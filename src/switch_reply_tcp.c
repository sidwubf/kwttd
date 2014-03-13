#include <unistd.h>
#include "kwttd_util.h"
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <xlocale.h>
#include <stdarg.h>
#include <arpa/inet.h>
#include <stdlib.h>

#define REQ_TURN_ON "101"
#define REQ_TURN_OFF "102"
#define REQ_GET "201"

#define TURN_ON  "302"
#define TURN_OFF "303"
#define GET_INFO "304"

#define MAX_PENDING 5

//302 REPLY: DONE TURN ON
//303 REPLY: DONE TURN OFF
//304 REPLY: MY INFORMATION IS ...

int
main(int argc, char *argv[]) {
	if (argc != 3) {
		fprintf(stderr, "Usage: %s <Port> <Mac>\n", argv[0]);
		exit(1);
	}

	int appSock;
	int switchSock;
	struct sockaddr_in appAddr;
	struct sockaddr_in switchAddr;
	unsigned short switchPort;
	unsigned int appAddrLen;
	unsigned int switchAddrLen;
	
	switchPort = atoi(argv[1]);
	
	if ((switchSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
		fprintf(stderr, "socket failed\n");
		exit(1);
	}
	
	memset(&switchAddr, 0, sizeof(switchAddr));
	switchAddr.sin_family = AF_INET;
	switchAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	switchAddr.sin_port = htons(switchPort);
	
	if (bind(switchSock, (struct sockaddr *) &switchAddr, sizeof(switchAddr)) < 0) {
		fprintf(stderr, "bind failed\n");
		exit(1);
	}
	
	if (listen(switchSock, MAX_PENDING) < 0) {
		fprintf(stderr, "listen failed\n");
		exit(1);
	}

	switchAddrLen = sizeof(switchAddr);
	if ((appSock = accept(switchSock, (struct sockaddr *) &appAddr, &appAddrLen)) < 0) {
		fprintf(stderr, "accept failed\n");
		exit(1);
	}
		
	char recvString[30];
	int recvStringLen;
		
	if ((recvStringLen = recv(appSock, recvString, 30, 0)) < 0) {
		fprintf(stderr, "recv failed\n");
		exit(1);
	}
	
	printf("Recv: %s\n", recvString);
		
	printf("App ip: %s\n", inet_ntoa(appAddr.sin_addr));
	
	char *type;
	type = kwttd_strsub(recvString, 0, 3);
	printf("Type: %s\n", type);

	char respString[40];
	int respStringLen;
	if (kwttd_strcmp(type, REQ_TURN_ON) == 0) {
		strcpy(respString, "302 REPLY: DONE TURN ON");
	} else if (kwttd_strcmp(type, REQ_TURN_OFF) == 0) {
		strcpy(respString, "303 REPLY: DONE TURN OFF");
	} else if (kwttd_strcmp(type, REQ_GET) == 0) {
		strcpy(respString, "304 REPLY: MY INFORMATION IS ...");
	} else {
	    fprintf(stderr, "Wrong type\n");
	    exit(1);	
	}
	
	printf("Resp: %s\n", respString);
	respStringLen = strlen(respString);
	if (send(appSock, respString, respStringLen, 0) != respStringLen) {
		fprintf(stderr, "send failed\n");
		exit(1);
	}
	
	exit(0);
}