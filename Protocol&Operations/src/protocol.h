/*
 ============================================================================
 Name        : protocol.h
 Author      : Basile Federico 759524
 Version     : 1.0
 Copyright   : //
 Description : Client/Server protocol header
 ============================================================================
 */

#ifndef PROTOCOL_H_
#define PROTOCOL_H_


#if defined WIN32
#include <winsock.h>
#else
#define closesocket close
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define BUFFER_SIZE 256
#define PROTOPORT 56700
#define NO_ERROR 0
#define LOCAL_HOST_ADDRESS "127.0.0.1"

// Prototypes
void errorhandler(char *errorMessage);
void clearWinsock();
int winCreateSock();


int winCreateSock() {

	WSADATA wsa_data;
	WORD version_requested;

	version_requested = MAKEWORD(2,2);
	int sock_result = WSAStartup(version_requested, &wsa_data);

	if(sock_result != NO_ERROR) {

		printf("Error at WSAStartup() \n");
		printf("A usable WinSock DLL cannot be found\n");
		return 0;
	}

	return 1;

}


void errorhandler(char *errorMessage) {

	printf("%s", errorMessage);
}


void clearWinsock() {

#if defined WIN32
	WSACleanup();
#endif
}

#endif /* PROTOCOL_H_ */
