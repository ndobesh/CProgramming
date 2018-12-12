#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

char *process(char[], int);

int main(void) {
    char buffer[256] = "GET LNAME";
    char *response = "I got your message";
    int size = sizeof(buffer) / sizeof(buffer[0]);

    printf("Response before processing: %s\n", buffer);

    response = process(buffer, size);

    printf("Response after processing: %s\n", response);


    return 0;
}

char *process(char buff[], int size) {
    char *firstWordFromBuffer = strtok(buff, " ");

    printf("First word from buffer before modification: %s\n", firstWordFromBuffer);

    for (int i = 0; firstWordFromBuffer[i]; i++) {
        firstWordFromBuffer[i] = tolower(firstWordFromBuffer[i]);
    }

    printf("First Word from buffer after modification: %s\n", firstWordFromBuffer);

    if (strcmp(firstWordFromBuffer, "get") == 0) {
        char *sortBy = strtok(NULL, " ");
        printf("Second word from buffer is: %s\n", sortBy);

        for (int i = 0; sortBy[i]; i++) {
            sortBy[i] = tolower(sortBy[i]);
        }
        printf("Second word from buffer after changing to lowercase: %s\n", sortBy);
        if (strcmp(sortBy, "lname") == 0) {
            //TODO:Return database sorted by last name
            printf("Second token is lname\n");
        } else if (strcmp(sortBy, "fname") == 0) {
            //TODO: Return database sorted by first name
            printf("Second token is fname\n");
        } else if (strcmp(sortBy, "sid") == 0) {
            //TODO: Return database sorted by SID
            printf("Second token is sid\n");
        } else if (strcmp(sortBy, "gpa") == 0) {
            //TODO: Return databasee sorted by GPA
            printf("Second token is gpa\n");
        } else {
            fprintf(stderr, "Error! Usage: get {lname, fname, SID, GPA}");
            exit(3);
        }

    }

    return firstWordFromBuffer;
}

