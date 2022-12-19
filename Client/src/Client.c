/*
 ============================================================================
 Name        : Client.c
 Author      : Basile Federico 759524
 Version     : 1.0
 Copyright   :
 Description : Client in UDP
 ============================================================================
 */

#include "../../Protocol&Operations/src/protocol.h"

int main(int argc, char *argv[]) {

	int port;
	char * dns = "";
	char * bash = argv[1];
	struct hostent *remoteHost;

	if(argc != 2) {

		errorhandler("Parameters not inserted. Retry.\n");
		return -1;
	}

#if defined WIN32
	if(winCreateSock() == 0) {

		return -1;
	}
#endif

	dns = strtok(bash, ":");
	port = atoi(strtok(NULL, ":"));
	remoteHost = gethostbyname(dns);

	if (remoteHost == NULL) {

		fprintf(stderr, "gethostbyname() failed.\n");
		return -1;
	}
	else {

		printf("Server name %s resolved - %s:%d\n", dns, inet_ntoa(*(struct in_addr *)remoteHost->h_addr), port);
	}

	int sock;

	if((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {

		errorhandler("socket() failed.\n");
		return -1;
	}

	struct sockaddr_in sad;
	memset(&sad, 0, sizeof(sad));

	sad.sin_family = AF_INET;
	sad.sin_port = htons(port);
	sad.sin_addr = *((struct in_addr *)remoteHost->h_addr);

	printf("Connecting to %s:%d...\n\n", dns, port);

	char expression[BUFFER_SIZE];

	do {

		memset(expression, 0, BUFFER_SIZE);

		printf("Insert an expression: (Close connection =, Addition +, Subtraction -, Multiplication *, Division /)\n");
		printf("Expression be like: + 23 45\n%c", '>');
		gets(expression);

		int exp_lenght;
		int sadSize = sizeof(sad);

		if((exp_lenght = strlen(expression)) > BUFFER_SIZE) {

			errorhandler("Expression too long. \n");
			return -1;
		}

		if(sendto(sock, expression, exp_lenght, 0, (struct sockaddr*)&sad, sizeof(sad)) != exp_lenght) {

			errorhandler("Client: sendto() sent a different number of bytes than expected");
			closesocket(sock);
			clearWinsock();
			return -1;
		}

		if (expression[0] != '=') {

			int bytes_rcvd;
			char result[BUFFER_SIZE];
			memset(result, 0, BUFFER_SIZE);

			if ((bytes_rcvd = recvfrom(sock, result, BUFFER_SIZE, 0, (struct sockaddr*)&sad, &sadSize)) <= 0) {

				errorhandler("Client: recvfrom() failed or connection closed prematurely");
				closesocket(sock);
				clearWinsock();
				return -1;
			}

			printf("\nReceived result from server %s, IP %s: %s\n\n", remoteHost->h_name, inet_ntoa(*(struct in_addr *)remoteHost->h_addr), result);	// aggiungere nome ip server
		}

	} while(expression[0] != '=');

	closesocket(sock);
	clearWinsock();
}
