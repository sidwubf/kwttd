#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>

int
main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "Usage: %s port\n", argv[0]);
    exit(1);
  }

  int sock, n;
  struct sockaddr_in servaddr, cliaddr;
  char recvstr[50];
  socklen_t cliaddrlen;

  if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
    fprintf(stderr, "socket failed\n");
    exit(1);
  }

  memset(&servaddr, 0, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(atoi(argv[1]));

  if (bind(sock, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
    fprintf(stderr, "bind failed\n");
    exit(1);
  }

  cliaddrlen = sizeof(cliaddr);
  if ((n = recvfrom(sock, recvstr, 50, 0, (struct sockaddr *) &cliaddr, &cliaddrlen)) < 0) {
    fprintf(stderr, "recvfrom failed\n");
    exit(1);
  }

  printf("client ip: %s, client port: %d\n", inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port));

  if (sendto(sock, "hello from server", 17, 0, (struct sockaddr *) (&cliaddr), sizeof(cliaddr)) == -1) {
    fprintf(stderr, "sendto failed\n");
    exit(1);
  }

  exit(0);
}
