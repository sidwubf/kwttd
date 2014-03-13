#include <xlocale.h>
#include "kwttd_util.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#define TURN_ON "101"
#define TURN_OFF "102"
#define TURN_ON_REPLY_LEN 23
#define TURN_OFF_REPLY_LEN 24

int
main(int argc, char *argv[]) {
    if (argc < 5) {
        fprintf(stderr, "Usage:  %s <Type> <IP> <Port> <Mac>\n", argv[0]);
        exit(1);
    }
	
	int sock;
	struct sockaddr_in switchAddr;
	unsigned short switchPort;
	char *switchIp;
	char *requireString;
	unsigned int requireStringLen;
	char *recvString;
	int recvStringLen;
	char *mac;
	char *type;
	
	//101 REQUIRE: xxxyyy TURN ON
	//102 REQUIRE: xxxyyy TURN OFF
	type = argv[1];
	mac = argv[4];
	if (kwttd_strcmp(type, TURN_ON) == 0) {
		strcpy(requireString, type);
		strcat(requireString, " REQUIRE: ");
		strcat(requireString, mac);
		strcat(requireString, " TURN ON");
		recvStringLen = TURN_ON_REPLY_LEN;
	} else if (kwttd_strcmp(type, TURN_OFF) == 0) {
		strcpy(requireString, type);
		strcat(requireString, " REQUIRE: ");
		strcat(requireString, mac);
		strcat(requireString, " TURN OFF");
		recvStringLen = TURN_OFF_REPLY_LEN;
	} else {
	    fprintf(stderr, "Usage:  %s <Type> <IP> <Port> <Mac>\n", argv[0]);
	    exit(1);	
	}

	if ((sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
		fprintf(stderr, "socket failed\n");
		exit(1);
	}
	
	switchIp = argv[2];
	switchPort = atoi(argv[3]);
	
	memset(&switchAddr, 0, sizeof(switchAddr));
	switchAddr.sin_family = AF_INET;
	switchAddr.sin_addr.s_addr = inet_addr(switchIp);
	switchAddr.sin_port = htons(switchPort);
	
	if (connect(sock, (struct sockaddr *) &switchAddr, sizeof(switchAddr)) < 0) {
		fprintf(stderr, "connect failed\n");
		exit(1);
	}
	
	requireStringLen = strlen(requireString);
	if (send(sock, requireString, requireStringLen, 0) != requireStringLen) {
		fprintf(stderr, "send failed\n");
		exit(1);
	}
	
	if ((recvStringLen = recv(sock, recvString, 30, 0)) <= 0) {
		fprintf(stderr, "recv failed\n");
		exit(1);
	}
	
	printf("Received: %s\n", recvString);
	
	close(sock);
	exit(0);
}