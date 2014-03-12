#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include "kwttd_util.h"

#define MAX_RECV_STR_LEN 255
#define DEFAULT_PORT 21151
#define SWITCH_NO_LEN 6

int
main(int argc, char *argv[]) {
    int sock;
    struct sockaddr_in clientAddr;
    struct sockaddr_in serverAddr;

    char recvString[MAX_RECV_STR_LEN+1];
    int recvStringLen;
    unsigned int clientAddrLen;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <Switch NO>\n", argv[0]);
        exit(1);
    }

    if ((sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
        fprintf(stderr, "socket failed\n");
        exit(1);
    }

    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddr.sin_port = htons(DEFAULT_PORT);

    if (bind(sock, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) < 0) {
        fprintf(stderr, "bind failed\n");
        exit(1);
    }

    clientAddrLen = sizeof(clientAddr);

    if ((recvStringLen = recvfrom(sock, recvString, MAX_RECV_STR_LEN, 0,
                                  (struct sockaddr *) &clientAddr, &clientAddrLen)) < 0) {
        fprintf(stderr, "recvfrom failed\n");
        exit(1);
    }

    recvString[recvStringLen] = '\0';
    printf("Received: %s\n", recvString);

    printf("Ip Address: %s\n", inet_ntoa(clientAddr.sin_addr));

    //who's no is NOxxxx
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
}
