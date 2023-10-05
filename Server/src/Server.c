/*
 ============================================================================
 Name        : Server.c
 Author      : Basile Federico 759524
 Version     : 1.0
 Copyright   :
 Description : Server in UDP
 ============================================================================
 */

// srv.di.uniba.it:56700

#include "../../Protocol&Operations/src/protocol.h"
#include "../../Protocol&Operations/src/operations.h"


int main(void) {

#if defined WIN32
	if(winCreateSock() == 0) {

		return -1;
	}
#endif

	int sock;

	struct sockaddr_in sad; // Server address structure
	memset(&sad, 0, sizeof(sad));

	struct sockaddr_in cad; // Client address structure
	memset(&cad, 0, sizeof(cad));

	int cadLenght = sizeof(cad); // Length client address

	if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {

		errorhandler("socket() failed.\n");
		clearWinsock();
		return -1;
	}

	sad.sin_family = AF_INET;
	sad.sin_addr.s_addr = inet_addr(LOCAL_HOST_ADDRESS);
	sad.sin_port = htons(PROTOPORT);


	if (bind(sock, (struct sockaddr*) &sad, sizeof(sad)) < 0) {

		errorhandler("bind() failed.\n");
		closesocket(sock);
		clearWinsock();
		return -1;
	}

	char operator;

	while (1) {	// Server never close

		puts("Server listening...");

		do {

			char expression[BUFFER_SIZE];
			memset(expression, 0, BUFFER_SIZE);


			if((recvfrom(sock, expression, BUFFER_SIZE, 0, (struct sockaddr*)&cad, &cadLenght)) < 0) {

				errorhandler("Server: recvfrom() received different number of bytes than expected.\n");
			}

			struct hostent *remoteHost = gethostbyaddr((char *) &cad.sin_addr.s_addr, sizeof(cad.sin_addr.s_addr), AF_INET);

			printf("Received expression \"%s\" from client %s, IP %s\n", expression, remoteHost->h_name, inet_ntoa(cad.sin_addr));

			char * token = NULL;

			token = strtok(expression, " ");
			operator = *token;

			if(operator != '=') {

				token = strtok(NULL, " ");
				char operand1_buf[(BUFFER_SIZE - 2)/2];	// Store at most 126 characters
				strcpy(operand1_buf, token);

				token = strtok(NULL, " ");
				char operand2_buf[(BUFFER_SIZE - 2)/2]; // Store at most 126 characters
				strcpy(operand2_buf, token);

				char result[BUFFER_SIZE];		// Answer to client
				memset(result, 0, BUFFER_SIZE); // Cleans result buffer
				int res_len;

				int operand1;
				sscanf(operand1_buf, "%d", &operand1);

				int operand2;
				sscanf(operand2_buf, "%d", &operand2);

				if(operand1_buf[0] == '-') {	// In case of a negative operand, this function allow to skip the 'isdigit' check

					strcpy(token, operand1_buf);
					token = strtok(operand1_buf, "-");
					strcpy(operand1_buf, token);
				}

				if(operand2_buf[0] == '-') {

					strcpy(token, operand2_buf);
					token = strtok(operand2_buf, "-");
					strcpy(operand2_buf, token);
				}

				if(!isdigit(*operand1_buf) || !isdigit(*operand2_buf)) {	// Checks if one of the two operands is a character

					strcpy(result, "Non-digit operand detected. Operation is not possible.");
					res_len = strlen(result);

					if (sendto(sock, result, res_len, 0, (struct sockaddr*)&cad, cadLenght) != res_len) {

						errorhandler("Server: sendto() sent a different number of bytes than expected. \n");
						closesocket(sock);
						clearWinsock();
						return -1;
					}
				}
				else if(operator == '+' || operator == '-' || operator == '*' || operator == '/') {

					switch(operator) {

					case '+':

						sprintf(result, "%d %c %d = %d", operand1, operator, operand2, sum(operand1, operand2));
						res_len = strlen(result);

						if (sendto(sock, result, res_len, 0, (struct sockaddr*)&cad, cadLenght) != res_len) {

							errorhandler("Server: send() sent a different number of bytes than expected. \n");
							closesocket(sock);
							clearWinsock();
							return -1;
						}
						break;

					case '-':

						sprintf(result, "%d %c %d = %d", operand1, operator, operand2, subtraction(operand1, operand2));
						res_len = strlen(result);

						if (sendto(sock, result, res_len, 0, (struct sockaddr*)&cad, cadLenght) != res_len) {

							errorhandler("Server: send() sent a different number of bytes than expected. \n");
							closesocket(sock);
							clearWinsock();
							return -1;
						}
						break;

					case '*':

						sprintf(result, "%d %c %d = %d", operand1, operator, operand2, multiplication(operand1, operand2));
						res_len = strlen(result);

						if (sendto(sock, result, res_len, 0, (struct sockaddr*)&cad, cadLenght) != res_len) {

							errorhandler("Server: send() sent a different number of bytes than expected. \n");
							closesocket(sock);
							clearWinsock();
							return -1;
						}
						break;

					case '/':

						if(operand2 == 0) {		// A/B where B = 0 error

							strcpy(result, "Divide by 0 error recognized. Impossible operation.");
							res_len = strlen(result);

						}
						else {

							sprintf(result, "%d %c %d = %.2f", operand1, operator, operand2, division(operand1, operand2)); // Result with 2 decimal digit
							res_len = strlen(result);
						}

						if (sendto(sock, result, res_len, 0, (struct sockaddr*)&cad, cadLenght) != res_len) {

							errorhandler("Server: send() sent a different number of bytes than expected. \n");
							closesocket(sock);
							clearWinsock();
							return -1;
						}
						break;

					}
				}
				else {

					strcpy(result, "Not recognized operation.");	// Wrong operator inserted but valid operand
					res_len = strlen(result);

					if (sendto(sock, result, res_len, 0, (struct sockaddr*)&cad, cadLenght) != res_len) {

						errorhandler("Server: send() sent a different number of bytes than expected");
						closesocket(sock);
						clearWinsock();
						return -1;
					}

				}
			}

		} while(operator != '=');	// Stop receiving expression from that specific client

		puts("");
	}
}
