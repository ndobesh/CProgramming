#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <ctype.h>

#define PORT_NUM 25000

char *GetCommand = "get";
char *PutCommand = "put";
char *DeleteCommand = "delete";
char *SaveCommand = "save";
char *StudentIdTitle = "SID";
char *LastNameTitle = "Lname";
char *FirstNameTitle = "Fname";
char *MiddleInitialTitle = "M";
char *GPA_Title = "GPA";
char *RecordHeaderPrintFormat = "| %-5s | %-9s | %-9s | %s | %-4s |\n";
char *RecordBorderPrintFormat = "+-------+-----------+-----------+---+------+";
char *RecordDataPrintFormat = "| %05lu | %-9s | %-9s | %c | %1.2f |\n";

typedef struct student {
    char lname[10];
    char initial;
    char fname[10];
    unsigned long SID;
    float GPA;
} SREC;

enum COMMAND {
    Invalid, Get, Put, Delete, Save
};

typedef enum COMMAND Command;

Command getCommand(const char *command);

void error(char *msg);

void startDatabaseSession(int sockfd);

void removeTrailingWhitespace(char *buffer);

void handleGetCommandResponse(int sockfd);

void printStudentRecords(SREC *studentRecords, int numberOfRecords);

void handleResponse(int sockfd, Command command);

void printServerResponse(int sockfd);


int main(void) {
    int sockfd;
    int portno;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    portno = PORT_NUM;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) { error("ERROR opening socket"); }
    server = gethostbyname("localhost");
    if (server == NULL) {
        fprintf(stderr, "ERROR, no such host\n");
        exit(0);
    }

    memset((char *) &serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    memcpy((char *) server->h_addr_list, (char *) &serv_addr.sin_addr.s_addr, (size_t) server->h_length);
    serv_addr.sin_port = htons((uint16_t) portno);

    if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        error("ERROR connecting");
    }

    startDatabaseSession(sockfd);

    close(sockfd);

    return 0;
}

void startDatabaseSession(int sockfd) {
    char commandBuffer[100];
    Command command;
    ssize_t n;

    do {
        printf("Enter next command> ");
        memset(commandBuffer, 0, 100);
        fgets(commandBuffer, 256, stdin);
        removeTrailingWhitespace(commandBuffer);
        command = getCommand(commandBuffer);

        if (command == Invalid) {
            printf("Command entered not valid.\n");
            continue;
        }

        n = write(sockfd, commandBuffer, strlen(commandBuffer));
        if (n < 0) {
            error("ERROR writing to socket");
        }

        handleResponse(sockfd, command);

    } while (command != Save);

    return;
}

void handleResponse(int sockfd, Command command) {
    switch (command) {
        case Invalid:
            puts("Invalid command should not have been sent to client");
            exit(1);

        case Get:
            handleGetCommandResponse(sockfd);
            return;

        case Put:
        case Delete:
        case Save:
            printServerResponse(sockfd);
            return;

        default:
            puts("Invalid command was passed to handleResponse function.");
            exit(1);
    }
}

void printServerResponse(int sockfd) {
    char buffer[30];
    memset(buffer, '\0', 30);

    read(sockfd, buffer, 30);
    puts(buffer);

    return;
}

void handleGetCommandResponse(int sockfd) {
    ssize_t n;
    int numberOfRecords = -1;
    SREC *studentRecords = NULL;
    int index;

    n = read(sockfd, &numberOfRecords, sizeof(int));
    if (n < 0) {
        error("ERROR writing to socket");
    }

    if (!numberOfRecords) {
        printStudentRecords(NULL, numberOfRecords);
        return;
    }

    studentRecords = malloc(sizeof(SREC) * numberOfRecords);


    for (index = 0; index < numberOfRecords; index++) {
        n = read(sockfd, &studentRecords[index], sizeof(SREC));
        if (n < 0) {
            error("ERROR reading from socket");
        }
    }

    printStudentRecords(studentRecords, numberOfRecords);
}

void printStudentRecords(SREC *studentRecords, int numberOfRecords) {
    int index;

    printf(RecordHeaderPrintFormat, StudentIdTitle, LastNameTitle, FirstNameTitle, MiddleInitialTitle, GPA_Title);
    puts(RecordBorderPrintFormat);

    for (index = 0; index < numberOfRecords; index++) {
        printf(RecordDataPrintFormat, studentRecords[index].SID, studentRecords[index].lname,
               studentRecords[index].fname, studentRecords[index].initial, studentRecords[index].GPA);
    }

    puts(RecordBorderPrintFormat);

}

Command getCommand(const char *fullCommand) {
    char *token = NULL;
    char *copy = NULL;

    copy = malloc(strlen(fullCommand) + 1);
    strcpy(copy, fullCommand);

    token = strtok(copy, " ");

    if (!strcmp(token, GetCommand)) {
        token = strtok(NULL, " ");

        if (!token) {
            return Invalid;
        }

        if (!strcmp(token, "lname"));
        else if (!strcmp(token, "fname"));
        else if (!strcmp(token, "SID"));
        else if (!strcmp(token, "GPA"));
        else {
            return Invalid;
        }

        free(copy);

        return Get;
    } else if (!strcmp(token, PutCommand)) {
        return Put;
    } else if (!strcmp(token, DeleteCommand)) {
        return Delete;
    } else if (!strcmp(token, SaveCommand)) {
        return Save;
    } else {
        return Invalid;
    }
}
void removeTrailingWhitespace(char *buffer) {
    ssize_t length = strlen(buffer);
    while (length - 1 >= 0 && isspace(buffer[length - 1])) {
        buffer[length - 1] = '\0';
        length--;
    }

    return;
}

void error(char *msg) {
    perror(msg);
    exit(0);
}
