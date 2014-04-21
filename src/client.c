#include <stdlib.h>//exit
#include <stdio.h>//fprintf
#include <sys/socket.h>//socket
#include <netinet/in.h>//IPPROTO_UDP
#include <netdb.h>//gethostbyname
#include <string.h>//memset
#include <arpa/inet.h>//inet_addr

int
main(int argc, char *argv[]) {
  if (argc < 3) {
    fprintf(stderr, "Usage: %s ip port\n", argv[0]);
    exit(1);
  }

  int sock;
  char *server_ip;
  unsigned short server_port;
  struct sockaddr_in cliAddr, serAddr;

  if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0)  {
    fprintf(stderr, "socket failed\n");
    exit(1);
  }

  server_ip = argv[1];
  server_port = atoi(argv[2]);

  memset(&cliAddr, 0, sizeof(cliAddr));
  cliAddr.sin_family = AF_INET;
  cliAddr.sin_addr.s_addr = htonl(INADDR_ANY);//inet_addr("127.0.0.1");
  cliAddr.sin_port = htons(21152);

  if (bind(sock, (struct sockaddr *) &cliAddr, sizeof(struct sockaddr)) < 0) {
    fprintf(stderr, "bind failed\n");
    exit(1);
  }

  memset(&serAddr, 0, sizeof(serAddr));
  serAddr.sin_family = AF_INET;
  serAddr.sin_addr.s_addr = inet_addr(server_ip);
  serAddr.sin_port = htons(server_port);

  if (sendto(sock, "hello", 5, 0, (struct sockaddr *) (&serAddr), sizeof(serAddr)) == -1) {
    fprintf(stderr, "sendto failed\n");
    exit(1);
  }

  printf("send success\n");

  int n;
  char recvstr[50];
  socklen_t seraddrlen;
  seraddrlen = sizeof(serAddr);
  if ((n = recvfrom(sock, recvstr, 50, 0, (struct sockaddr *) &serAddr, &seraddrlen)) < 0) {
    fprintf(stderr, "recvfrom failed\n");
    exit(1);
  }

  printf("receive success: %s\n", recvstr);

  exit(0);
}
