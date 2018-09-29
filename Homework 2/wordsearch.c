#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <memory.h>

#define MAXENTRIES 50


//TODO: Create array of whatever size data1/2/3 wordsearch is
//TODO: Take out spaces of inputted 2D array so that I can process it
//TODO: Store words after 2D array in file to be compared against
//TODO: Output results
int main(int argc, char *argv[]) {

    FILE *myFile = fopen(argv[1], "r");
    if (myFile == NULL) {
        fprintf(stderr, "Failed to open file\n");
        exit(1);
    }

    //Input Validation
    assert(argc > 1);

    //DEBUG Statement
    /*printf("This will print if assertion is true");*/

    char firstLine[MAXENTRIES];

    fgets(firstLine, MAXENTRIES, myFile);

    //DEBUG: Used to see what is put in firstLine by fgets function.
    printf("%s\n", firstLine);

    //This will be used to create 2D array size later
    size_t numberofElementsWithSpaces = strlen(firstLine);

    //DEBUG Statement
    /*printf("Length of first line is: %zu\n", numberofElementsWithSpaces);*/

    char ArrayWithoutSpaces[(numberofElementsWithSpaces - 1) / 2][(numberofElementsWithSpaces - 1) / 2];


    fclose(myFile);
    return 0;
}

