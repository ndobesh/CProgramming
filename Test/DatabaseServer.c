#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <time.h>

#define FILE_NAME "Student_Records.out"
#define PORT_NUM 25000

typedef struct student {
    char lname[10];
    char initial;
    char fname[10];
    unsigned long SID;
    float GPA;
} SREC;

typedef struct node {
    struct node *next;
    SREC *data;
} Node;

int
putRecord(Node *f, Node *l, Node *s, Node *g, const char *cmd, const char *s_gpa, const char *s_sid, const char *first,
          const char *init, const char *last);

int saveNodes(FILE *fp, Node *start);

void sendRecords(Node *start, int numberOfRecords, int handle);

void error(char *msg);

Node *createNode();

Node *deleteNode(Node *, unsigned long, int *);

void add(Node *node, SREC *rec);

void swapNodes(Node *alpha, Node *beta);

/* Sorting */
Node *bubbleSortByFirst(Node *top);

Node *bubbleSortByLast(Node *top);

Node *bubbleSortBySID(Node *top);

Node *bubbleSortByGPA(Node *top);

void sortAll(Node *fName, Node *lName, Node *SID, Node *GPA);

/* Utility */
unsigned long getSID(const char *s_SID);

int getTypeID(char *type);

int getCommand(char *cmd);

SREC *newSREC(const char *last, char init, const char *first, unsigned long SID, float GPA);

char *successfulPutResponse = "Record successfully added.";
char *unsuccessfulPutResponse = "Error while adding record.";
char *unsuccessfulSaveResponse = "Error while saving database.";
char *successfulSaveResponse = "Database saved successfully.";
char *successfulDeleteResponse = "Record deleted.";
char *unsuccessfulDeleteResponse = "Unable to delete record.";

int main(void) {
    int sockfd;
    int newsockfd;
    int portno;
    socklen_t clilen;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    int n;

    int numRecords = 0;
    int commandID;
    unsigned long tempSID;

    Node *fNameHead = NULL;
    Node *lNameHead = NULL;
    Node *SIDHead = NULL;
    Node *GPAHead = NULL;

    FILE *dataFile = NULL;

    /* Create a socket and make sure socket was successfully opened */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        error("ERROR opening socket");
    }

    memset((char *) &serv_addr, 0, sizeof(serv_addr));
    portno = PORT_NUM;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons((uint16_t) portno);
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        error("ERROR on binding");
    }
    listen(sockfd, 5);

    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);

    if (newsockfd < 0) {
        error("ERROR on accept");
    }

    fNameHead = createNode();
    lNameHead = createNode();
    SIDHead = createNode();
    GPAHead = createNode();

    for (;;) {
        memset(buffer, 0, 256);
        n = (int) read(newsockfd, buffer, 255);
        if (n <= 0) {
            error("ERROR reading from socket");
        }

        commandID = getCommand(strtok(buffer, " "));

        if (commandID == 0) {
            n = getTypeID(strtok(NULL, " "));
            if (n == 0) {
                sendRecords(fNameHead, numRecords, newsockfd);
            } else if (n == 1) {
                sendRecords(lNameHead, numRecords, newsockfd);
            } else if (n == 2) {
                sendRecords(SIDHead, numRecords, newsockfd);
            } else if (n == 3) {
                sendRecords(GPAHead, numRecords, newsockfd);
            } else {
                sendRecords(NULL, 0, newsockfd);
            }
        }

        if (commandID == 1) { /*put*/
            if (putRecord(fNameHead, lNameHead, SIDHead, GPAHead,
                          strtok(buffer, ","), strtok(NULL, ","), strtok(NULL, ","),
                          strtok(NULL, ","), strtok(NULL, ","), strtok(NULL, ",")) == 1) {
                numRecords++;
                sortAll(fNameHead, lNameHead, SIDHead, GPAHead);
                write(newsockfd, successfulPutResponse, strlen(successfulPutResponse));
            } else {
                write(newsockfd, unsuccessfulPutResponse, strlen(unsuccessfulPutResponse));
            }
        }

        if (commandID == 2) { /*delete*/
            tempSID = getSID(strtok(NULL, " "));

            fNameHead = deleteNode(fNameHead, tempSID, &n);
            lNameHead = deleteNode(lNameHead, tempSID, &n);
            SIDHead = deleteNode(SIDHead, tempSID, &n);
            GPAHead = deleteNode(GPAHead, tempSID, &n);

            if (n == 0) {
                write(newsockfd, unsuccessfulDeleteResponse, strlen(unsuccessfulDeleteResponse));
            } else {
                numRecords--;
                sortAll(fNameHead, lNameHead, SIDHead, GPAHead);
                write(newsockfd, successfulDeleteResponse, strlen(successfulDeleteResponse));
            }
        }

        if (commandID == 3) { /*save*/
            break;
        }
    }

    dataFile = fopen(FILE_NAME, "w");
    if (dataFile == NULL) {
        fprintf(stderr, "Unable to data file.\n");
        write(newsockfd, unsuccessfulSaveResponse, strlen(unsuccessfulSaveResponse));
    } else {
        saveNodes(dataFile, SIDHead);
        fclose(dataFile);
        write(newsockfd, successfulSaveResponse, strlen(successfulSaveResponse));
    }

    close(newsockfd);
    return 0;
}

/* Saves all the nodes under the start node provided.
        Given a file pointer */
int saveNodes(FILE *fp, Node *start) {
    while (start != NULL && start->data != NULL) {
        fwrite(start->data, sizeof(SREC), 1, fp);
        start = start->next;
    }

    return 1;
}

/*Utility function convert from a string to an unsigned long */
unsigned long getSID(const char *s_SID) {
    char *temp;  /*strtoul puts the rest of the text in temp after converting */
    return strtoul(s_SID, &temp, 10);
}

/*Sends records to the place specified by the handle. */
void sendRecords(Node *start, int numberOfRecords, int handle) {
    int c = 0;
    Node *temp = start;

    write(handle, &numberOfRecords, sizeof(int));

    if (numberOfRecords == 0) { /*No records to write. */
        return;
    }

    while (c < numberOfRecords) {
        write(handle, temp->data, sizeof(SREC));
        temp = temp->next;
        c++;
    }
}

/* Creates a Node */
Node *createNode() {
    Node *t;
    t = malloc(sizeof(Node));
    t->data = NULL;
    t->next = NULL;
    return t;
}

/*strtok calls are called right to left, so SREC is backwards. */
int
putRecord(Node *f, Node *l, Node *s, Node *g, const char *cmd, const char *s_gpa, const char *s_sid, const char *init,
          const char *first, const char *last) {
    unsigned long SID;
    float GPA;
    SREC *temp;

    if (cmd == NULL || s_gpa == NULL || s_sid == NULL || init == NULL || first == NULL || last == NULL) {
        return 0;
    }


    SID = getSID(s_sid);
    GPA = (float) atof(s_gpa);
    if (SID == 0 || GPA == 0) {
        return 0;
    }

    temp = newSREC(last, init[0], first, SID, GPA);
    add(f, temp);
    add(l, temp);
    add(s, temp);
    add(g, temp);

    return 1;
}

/* Adds Data to a new node appended to the end of the last node */
void add(Node *node, SREC *rec) {
    Node *temp;
    temp = node;

    /*Head node case. You need data, not another node. */
    if (temp->data == NULL) {
        temp->data = rec;
        return;
    }

    while (temp->next != NULL) {
        temp = temp->next;
    }

    temp->next = createNode();
    temp->next->data = rec;
}

Node *deleteNode(Node *head, unsigned long SID, int *result) {
    Node *checking;

    checking = head;
    if (head->data->SID == SID) {
        if (head->next == NULL) {
            return createNode();
        }
        return head->next;
    }

    while (checking != NULL) {
        if (checking->next != NULL) {
            if (checking->next->data->SID == SID) { /*Delete it. */
                if (checking->next->next != NULL) { /*Is there one after the one we found? */
                    checking->next = checking->next->next;
                    (*result) = 1;
                    return head;
                } else { /*The last element is the one... */
                    checking->next = NULL;
                    (*result) = 1;
                    return head;
                }
            }
        }
        checking = checking->next;
    }

    (*result) = 0;
    return head;
}

void sortAll(Node *fName, Node *lName, Node *SID, Node *GPA) {
    bubbleSortByFirst(fName);
    bubbleSortByLast(lName);
    bubbleSortBySID(SID);
    bubbleSortByGPA(GPA);
}

void swapNodes(Node *alpha, Node *beta) {
    SREC *tempRecord = alpha->data;
    alpha->data = beta->data;
    beta->data = tempRecord;
}

SREC *newSREC(const char *last, char init, const char *first, unsigned long SID, float GPA) {
    SREC *temp = malloc(sizeof(SREC));

    /* They're arrays they don't need mallocing*/
    strncpy(temp->lname, last, 9);

    /* They're arrays, we good.*/
    strncpy(temp->fname, first, 9);

    /* Addition made by OM. Initial wasn't initialized */
    temp->initial = init;

    temp->SID = SID;

    temp->GPA = GPA;

    return temp;

}

/* Utility that takes a string and identifies what command ID it is. */
int getCommand(char *cmd) {
    if (strcmp(cmd, "get") == 0) {
        return 0;
    }

    if (strcmp(cmd, "put") == 0) {
        return 1;
    }

    if (strcmp(cmd, "delete") == 0) {
        return 2;
    }

    if (strcmp(cmd, "save") == 0) {
        return 3;
    }

    return -1;
}

/*Takes a type string and converts it to an id.
        Types are the fname, lname, SID, GPA  from get commands*/
int getTypeID(char *type) {
    if (type == NULL) {
        return -1;
    }

    if (strcmp(type, "fname") == 0) {
        return 0;
    }

    if (strcmp(type, "lname") == 0) {
        return 1;
    }

    if (strcmp(type, "SID") == 0) {
        return 2;
    }

    if (strcmp(type, "GPA") == 0) {
        return 3;
    }

    return -1;
}

Node *bubbleSortByFirst(Node *top) {
    int hasSwapped;
    int strcmpResult;

    Node *alpha;

    /* Nothing needs sorting. Only have one thing. */
    if (top->next == NULL) {
        return top;
    }

    do {
        hasSwapped = 0; /*FALSE*/
        alpha = top;

        while (alpha->next != NULL) { /*While we have something to possibly swap... */
            strcmpResult = strcmp(alpha->data->fname, alpha->next->data->fname);

            if (strcmpResult > 0) {
                swapNodes(alpha, alpha->next);
                hasSwapped = 1; /*Aye! We swapped. Gotta go again! */
            }

            alpha = alpha->next;
        }

    } while (hasSwapped);

    /* The data has changed. Not the actual pointer it self. */
    return top;
}

Node *bubbleSortByLast(Node *top) {
    int hasSwapped;
    int strcmpResult;

    Node *alpha;

    /* Nothing needs sorting. Only have one thing. */
    if (top->next == NULL) {
        return top;
    }

    do {
        hasSwapped = 0; /*FALSE*/
        alpha = top;

        while (alpha->next != NULL) { /*While we have something to possibly swap... */
            strcmpResult = strcmp(alpha->data->lname, alpha->next->data->lname);

            if (strcmpResult > 0) {
                swapNodes(alpha, alpha->next);
                hasSwapped = 1; /*Aye! We swapped. Gotta go again! */
            }

            alpha = alpha->next;
        }

    } while (hasSwapped);

    /* The data has changed. Not the actual pointer it self. */
    return top;
}

Node *bubbleSortBySID(Node *top) {
    int hasSwapped;

    Node *alpha;

    /* Nothing needs sorting. Only have one thing. */
    if (top->next == NULL) {
        return top;
    }

    do {
        hasSwapped = 0; /*FALSE*/
        alpha = top;

        while (alpha->next != NULL) { /*While we have something to possibly swap... */

            if (alpha->data->SID > alpha->next->data->SID) {
                swapNodes(alpha, alpha->next);
                hasSwapped = 1; /*Aye! We swapped. Gotta go again! */
            }

            alpha = alpha->next;
        }

    } while (hasSwapped);

    /* The data has changed. Not the actual pointer it self. */
    return top;
}

Node *bubbleSortByGPA(Node *top) {
    int hasSwapped;

    Node *alpha;

    /* Nothing needs sorting. Only have one thing. */
    if (top->next == NULL) {
        return top;
    }

    do {
        hasSwapped = 0; /*FALSE*/
        alpha = top;

        while (alpha->next != NULL) { /*While we have something to possibly swap... */

            if (alpha->data->GPA < alpha->next->data->GPA) {
                swapNodes(alpha, alpha->next);
                hasSwapped = 1; /*Aye! We swapped. Gotta go again! */
            }

            alpha = alpha->next;
        }

    } while (hasSwapped);

    /* The data has changed. Not the actual pointer it self. */
    return top;
}

void error(char *msg) {
    printf("%s\n", msg);
    exit(0);
}


