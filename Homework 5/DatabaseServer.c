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

void process(char buffer[256]);

void validate(char *buffer);

SREC studentRecord;

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

        process(buffer);

        printf("Received message from the client: %s", buffer);

        /* Send the length field */
        length = (int) strlen(response);
        write_length(newsockfd, (size_t) length);

        /* Send the message field */
        writen(newsockfd, response, (size_t) length);
    }
}

//TODO: Validate input
//Function processes data sent from client
void process(char buffer[256]) {
    char *commandFromBuffer;
    FILE *file;
    char s[60]; //buffer for files

    //pointer to properly indented output
    sprintf(s, "records.out");
    if ((file = fopen(s, "w+")) == NULL) {
        fprintf(stderr, "Failed to open file\n");
        exit(1);
    }

    //TODO: Create case statement based on first word of buffer
    commandFromBuffer = strtok(buffer, " ");
    for (int i = 0; commandFromBuffer[i]; i++) {
        commandFromBuffer[i] = tolower(commandFromBuffer[i]);
    }
    /*strlwr(commandFromBuffer);*/
    if (strcmp(commandFromBuffer, "get") == 0) {
        //TODO: Do something
        char *sortBy = strtok(NULL, " ");
        for (int i = 0; sortBy[i]; i++) {
            sortBy[i] = tolower(sortBy[i]);
        }
        //if/else statement for all get combinations
        if (strcmp(sortBy, "lname") == 0) {
            //TODO:Return database sorted by last name
        } else if (strcmp(sortBy, "fname") == 0) {
            //TODO: Return database sorted by first name
        } else if (strcmp(sortBy, "sid") == 0) {
            //TODO: Return database sorted by SID
        } else if (strcmp(sortBy, "gpa") == 0) {
            //TODO: Return databasee sorted by GPA
        } else {
            fprintf(stderr, "Error! Usage: get {lname, fname, SID, GPA}");
            exit(3);
        }
    } else if (strcmp(commandFromBuffer, "put") == 0) {
        //TODO:Assign tokens from put statement into struct
        //Something tells me this isn't going to work...
        /*char templname[10] = " ";
        char tempfname[10] = " ";
        tempfname[0] = *strtok(NULL, ",");
        *studentRecord.fname = (char) tempfname;
        templname[0] = *strtok(NULL, ",");
        *studentRecord.lname = (char) templname;*/
        /*studentRecord.initial = (char) strtok(NULL, ",");
        studentRecord.SID = (unsigned long) strtok(NULL, ",");
        studentRecord.GPA = strtok(NULL, ",");*/
    } else if (strcmp(commandFromBuffer, "delete") == 0) {
        //TODO: Delete struct student Record based off of SID
        /*int SID = atoi(strtok(NULL," "));
        linked_delete(studentRecord, SID);*/
    }
        //The server saves data to the file and the client exits.
    else if (strcmp(commandFromBuffer, "save") == 0) {
        //TODO: Output to file.
        //HINT: Use code from A4
        /*linked_print(*//*datarecords*//*);*/
        exit(4);
    } else {
        //Handles error if one of the commands isn't entered.
        //Should not be hit because of the validate function.
        fprintf(stderr, "Invalid command! First word must be either get, put, delete, or save\n");
        exit(2);
    }
    fclose(file);
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
