#include "kwttd_network.h"
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <net/if.h>
#include <sys/ioctl.h>

char
*get_broadcast_ip() {
    int sockfd;
    struct ifreq ifr;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    bzero(&ifr, sizeof(ifr));
    strcpy(ifr.ifr_name, "en0");
    if (ioctl(sockfd, SIOCGIFBRDADDR, &ifr) < 0)
        perror("ioctl");

    close(sockfd);

    return inet_ntoa(((struct sockaddr_in *) &(ifr.ifr_addr))->sin_addr);
}
