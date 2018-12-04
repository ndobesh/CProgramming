/* A simple client in the internet domain using TCP
   The hostname and port number is passed as arguments*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include "util.h"

int main(int argc, char *argv[]) {
    int sockfd, portno;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char buffer[256];

    if (argc < 3) {
        fprintf(stderr, "Usage: %s hostname port\n", argv[0]);
        exit(1);
    }

    portno = atoi(argv[2]);

    /*
     * Step 1 Create socket.
     */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0)
        error("ERROR opening socket");

    /* gethostbyname() takes host domain name and resolves it to an address */
    server = gethostbyname(argv[1]);

    if (server == NULL) {
        fprintf(stderr, "ERROR, no such host\n");
        exit(0);
    }

    /* 0 out the server address stuct and set members */
    memset((char *) &serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    memcpy((char *) server->h_addr_list, (char *) &serv_addr.sin_addr.s_addr, (size_t) server->h_length);
    serv_addr.sin_port = htons((uint16_t) portno);

    if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
        error("ERROR connecting");

    for (;;) {
        size_t length;

        printf("Please enter the message: ");

        fgets(buffer, sizeof(buffer) - 1, stdin);

        length = strlen(buffer);

        write_length(sockfd, length);
        writen(sockfd, buffer, length);

        length = read_length(sockfd);

        if (length >= sizeof(buffer))
            error("Response message exceeds the buffer size");

        readn(sockfd, buffer, length);
        buffer[length] = '\0';

        printf("%s\n", buffer);
    }
}
