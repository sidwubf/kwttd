#include "kwttd_network.h"
#include <stdio.h>      /* printf fprintf */
#include <stdlib.h>  /* exit */
#include <netinet/in.h> /* sockaddr_in */
#include <string.h> /* strcat */
#include <arpa/inet.h> /* inet_addr */
#include <unistd.h> /* sleep */

int
main(int argc, char *argv[]) {
    // 001 NOTIFY: WHO'S MAC STARTS WITH xxxx
	int sock;                         /* Socket */
    struct sockaddr_in broadcastAddr; /* Broadcast address */
	char *broadcastIp;
    unsigned short broadcastPort;     /* Server port */
	char *startMac;
    char *sendString;                 /* String to broadcast */
    int broadcastPermission;          /* Socket opt to set permission to broadcast */
    unsigned int sendStringLen;       /* Length of string to broadcast */

    if (argc < 3) {
        fprintf(stderr, "Usage:  %s <Port> <MAC>\n", argv[0]);
        exit(1);
    }

    broadcastIp = get_broadcast_ip();
    printf("broadcast:%s\n", broadcastIp);
    broadcastPort = atoi(argv[1]);
	sendString = argv[2];
	printf("send string: %s\n", sendString);

	if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
		fprintf(stderr, "socket failed\n");
		exit(1);
	}

    /* Set socket to allow broadcast */
    broadcastPermission = 1;
    if (setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (void *) &broadcastPermission, sizeof(broadcastPermission)) < 0) {
		fprintf(stderr, "setsockopt failed\n");
		exit(1);
	}

    /* Construct local address structure */
    memset(&broadcastAddr, 0, sizeof(broadcastAddr));   /* Zero out structure */
    broadcastAddr.sin_family = AF_INET;                 /* Internet address family */
    broadcastAddr.sin_addr.s_addr = inet_addr(broadcastIp);/* Broadcast IP address */
    broadcastAddr.sin_port = htons(broadcastPort);         /* Broadcast port */

    sendStringLen = strlen(sendString);  /* Find length of sendString */
    for (;;) {
        /* Broadcast sendString in datagram to clients every 3 seconds*/
        if (sendto(sock, sendString, sendStringLen, 0, (struct sockaddr *) &broadcastAddr, sizeof(broadcastAddr)) != sendStringLen) {
        	fprintf(stderr, "sendto failed\n");
			exit(1);
        }

        sleep(3);   /* Avoids flooding the network */
    }

    exit(0);
}
