#include "kwttd_util.h"
#include <xlocale.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

#define NOTIFY "001"

#define MAX_RECV_STR_LEN 50

int
main(int argc, char *argv[]) {
	if (argc != 3) {
		fprintf(stderr, "Usage: %s <Port> <Mac>\n", argv[0]);
		exit(1);
	}

	int sockfd;
	struct sockaddr_in appAddr;
	struct sockaddr_in switchAddr;
	unsigned int switchAddrLen;
	char recvString[MAX_RECV_STR_LEN+1];
	int recvStringLen;
	unsigned short port;
	char *mac;
	char *requestType;
	char *macStart;
	char respString[42];
	
	if ((sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
		fprintf(stderr, "socket failed\n");
		exit(1);
	}
	
	port = atoi(argv[1]);
	
	memset(&appAddr, 0, sizeof(appAddr));
	appAddr.sin_family = AF_INET;
	appAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	appAddr.sin_port = htons(port);

	if (bind(sockfd, (struct sockaddr *) &appAddr, sizeof(appAddr)) < 0) {
		fprintf(stderr, "bind failed\n");
		exit(1);
	}
	
	switchAddrLen = sizeof(switchAddr);
    if ((recvStringLen = recvfrom(sockfd, recvString, MAX_RECV_STR_LEN, 0,
                                  (struct sockaddr *) &switchAddr, &switchAddrLen)) < 0) {
        fprintf(stderr, "recvfrom failed\n");
        exit(1);
    }
	
    recvString[recvStringLen] = '\0';
    printf("Received: %s\n", recvString);
	requestType = kwttd_strsub(recvString, 0, 3);
	printf("Type: %s\n", requestType);

	if (kwttd_strcmp(requestType, NOTIFY) == 0) {
		macStart = kwttd_strsub(recvString, 34, recvStringLen-34);
		mac = argv[2];
		if (kwttd_strstartwith(macStart, mac) == 0) {
			printf("Yes, my mac starts with: %s\n", macStart);
			printf("And my whole mac is: %s\n", mac);
			strcpy(respString, "301 REPLY: MY MAC IS ");
			strcat(respString, mac);
	        if (sendto(sockfd, respString, sizeof(respString), 0,
	                   (struct sockaddr *) &switchAddr, sizeof(switchAddr))) {
	            printf("Responce: %s\n", respString);
	        }
		}
	} else {
		printf("Type incorrent\n");
	}

	printf("Ip Address: %s\n", inet_ntoa(switchAddr.sin_addr));
	close(sockfd);
	exit(0);

	/*
    char *sw_no;
    sw_no = kwttd_strsub(argv[1], 12, SWITCH_NO_LEN);
    if (kwttd_strcmp(sw_no, argv[0]) > 0) {
        char *resp;
        resp = strcat(sw_no, " is me.");
        // NOxxxx is me.
        printf("My switch no is: %s\n", sw_no);
        if (sendto(sock, resp, sizeof(resp), 0,
                   (struct sockaddr *) &clientAddr, sizeof(clientAddr))) {
            printf("%s\n", resp);
        }
    } else {
        printf("My switch no is not: %s\n", sw_no);
    }

    close(sock);
	exit(0);
	*/
}