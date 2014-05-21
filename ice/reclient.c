#include <stdio.h>      /* for printf() and fprintf() */
#include <sys/socket.h> /* for socket(), connect(), sendto(), and recvfrom() */
#include <arpa/inet.h>  /* for sockaddr_in and inet_addr() */
#include <stdlib.h>     /* for atoi() and exit() */
#include <string.h>     /* for memset() */
#include <unistd.h>     /* for close() */
#include <sys/types.h>
#include <netdb.h>
#include <time.h>

#define ECHOMAX 255     /* Longest string to echo */

void DieWithError(char *errorMessage);  /* External error handling function */

int hostname_to_ip(char *hostname, char *ip);

int main(int argc, char *argv[])
{
    int sock;                        /* Socket descriptor */
    struct sockaddr_in echoServAddr; /* Echo server address */
    struct sockaddr_in fromAddr;     /* Source address of echo */
    struct sockaddr_in cliAddr;
    unsigned short echoServPort;     /* Echo server port */
    unsigned short cliPort;
    unsigned int fromSize;           /* In-out of address size for recvfrom() */
    char *servHostname;              /* IP address of server */
    char *servIP;
    char *echoString;                /* String to send to echo server */
    char echoBuffer[ECHOMAX+1];      /* Buffer for receiving echoed string */
    int echoStringLen;               /* Length of string to echo */
    int respStringLen;               /* Length of received response */
    int sleepSeconds;

    if ((argc < 3) || (argc > 6))    /* Test for correct number of arguments */
    {
        fprintf(stderr,"Usage: %s <Server IP> <Echo Word> <Echo Port> <Port> <Sleep Seconds>\n", argv[0]);
        exit(1);
    }

    //servHostname = argv[1];
    //hostname_to_ip(servHostname, servIP);
    servIP = argv[1];
    echoString = argv[2];       /* Second arg: string to echo */

    if ((echoStringLen = strlen(echoString)) > ECHOMAX)  /* Check input length */
        DieWithError("Echo word too long");

    echoServPort = atoi(argv[3]);  /* Use given port, if any */
    cliPort = atoi(argv[4]);
    sleepSeconds = atoi(argv[5]);

    /* Create a datagram/UDP socket */
    if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
        DieWithError("socket() failed");

    memset(&cliAddr, 0, sizeof(cliAddr));
    cliAddr.sin_family = AF_INET;
    cliAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    cliAddr.sin_port = htons(cliPort);

    bind(sock, (struct sockaddr *) &cliAddr, sizeof(cliAddr));

    /* Construct the server address structure */
    memset(&echoServAddr, 0, sizeof(echoServAddr));    /* Zero out structure */
    echoServAddr.sin_family = AF_INET;                 /* Internet addr family */
    echoServAddr.sin_addr.s_addr = inet_addr(servIP);  /* Server IP address */
    echoServAddr.sin_port   = htons(echoServPort);     /* Server port */

    time_t now;
    struct tm *tm;

    for ( ; ; ) {
        /* Send the string to the server */
        if (sendto(sock, echoString, echoStringLen, 0, (struct sockaddr *)
                   &echoServAddr, sizeof(echoServAddr)) != echoStringLen)
            DieWithError("sendto() sent a different number of bytes than expected");

        now = time(0);
        if ((tm = localtime (&now)) == NULL) {
            printf ("Error extracting time stuff\n");
            return 1;
        }

        printf ("%04d-%02d-%02d %02d:%02d:%02d\n",
        tm->tm_year+1900, tm->tm_mon+1, tm->tm_mday,
        tm->tm_hour, tm->tm_min, tm->tm_sec);

        sleep(sleepSeconds);
    }

    close(sock);
    exit(0);
}
