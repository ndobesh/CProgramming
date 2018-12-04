/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "util.h"

int main(int argc, char *argv[]) {
    int sockfd, newsockfd, portno;
    socklen_t clilen;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        exit(1);
    }

    portno = atoi(argv[1]);

    /*
     * STEP 1 Create the socket.
     */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0)
        error("Error opening socket");

    /*
     * STEP 2 Prepare and bind to the server address.
     */
    memset((char *) &serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons((uint16_t) portno);

    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
        error("Error binding socket");

    /*
     * STEP 3 Open server up for listening.
     */
    if (listen(sockfd, 5) < 0)
        error("Error listening on socket");

    /*
     * STEP 4 Accept incoming connections.
     */
    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
    if (newsockfd < 0)
        error("Error accepting connection");

    /*
     * Communicate with the client.
     */
    memset(buffer, 0, 256);

    for (;;) {
        int length;
        char *response = "I got your message";

        /* Read the length field */
        length = (int) read_length(newsockfd);

        if (length >= sizeof(buffer))
            error("Message exceeds the buffer size");

        /* Read the message field */
        readn(newsockfd, buffer, (size_t) length);
        buffer[length] = '\0';

        printf("Received message from the client: %s", buffer);

        /* Send the length field */
        length = (int) strlen(response);
        write_length(newsockfd, (size_t) length);

        /* Send the message field */
        writen(newsockfd, response, (size_t) length);
    }
}