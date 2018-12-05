#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "util.h"

#define PORT_NUM 25001

typedef struct student {
    char lname[10];
    char initial;
    char fname[10];
    unsigned long SID;
    float GPA;
} SREC;

typedef struct node {
    int data; /*Or whatever data you need to orginize*/
    struct node *next;
} Node;

void linked_insert(Node **nodePtr, int value);

int linked_delete(Node **nodePtr, int value);

int linked_isEmpty(Node *nodePtr);

void linked_print(Node *nodePtr);

int main(void) {
    int sockfd, newsockfd, portno;
    socklen_t clilen;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;

    portno = PORT_NUM;

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

void linked_insert(Node **nodePtr, int value) {
    Node *newNode;
    Node *previous;
    Node *current;

    newNode = (Node *) malloc(sizeof(Node));

    if (newNode != NULL) /*make sure memory was available*/
    {
        newNode->data = value;
        newNode->next = NULL;

        previous = NULL;
        current = *nodePtr;

        /*Traverses list until end or larger data is found
          If order doesn't matter, only append to the end
          by removing second condition or insert at the beginning
        in constant time*/
        while (current != NULL && value > current->data) {
            previous = current;
            current = current->next;
        }

        if (previous == NULL) /*newNode is placed at the beginning*/
        {
            newNode->next = *nodePtr;
            *nodePtr = newNode;
        } else /*newNode is placed in middle or end*/
        {
            previous->next = newNode;
            newNode->next = current;
        }
    } else {
        printf("%d not inserted\n", value);
    }
}

int linked_delete(Node **nodePtr, int value) {
    Node *previous;
    Node *current;
    Node *temp;

    /*First node is to be deleted*/
    if (value == (*nodePtr)->data) {
        temp = *nodePtr; /*retain pointer to memory to be freed*/
        *nodePtr = (*nodePtr)->next;
        free(temp);
        return value;
    } else {
        /*Must retain the previous to connect it
          to the node after the one that is
          going to be deleted*/
        previous = *nodePtr;
        current = (*nodePtr)->next; /*parens needed to force correct order of ops*/

        /*loop through nodes until the value is found*/
        while (current != NULL && current->data != value) {
            previous = current;
            current = current->next;
        }

        /*delete current node if not NULL
          if node is NULL then the value
          was not in list*/
        if (current != NULL) {
            previous->next = current->next;
            free(current);
            return value;
        }
    }
    /*value not found, return -1 to show
      no node removed*/
    return -1;

}

int linked_isEmpty(Node *nodePtr) {
    return nodePtr == NULL;
}

void linked_print(Node *nodePtr) {
    if (linked_isEmpty(nodePtr)) {
        printf("List is empty\n");
    } else {
        while (nodePtr != NULL) {
            printf("%d --> ", nodePtr->data);
            nodePtr = nodePtr->next;
        }

        printf("NULL\n");
    }
}
