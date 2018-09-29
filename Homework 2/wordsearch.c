#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <memory.h>

#define MAXENTRIES 50


//TODO: Create array of whatever size data1/2/3 word search is
//TODO: Take out spaces of inputted 2D array so that I can process it
//TODO: Store words after 2D array in file to be compared against
//TODO: Output results
int main(int argc, char *argv[]) {

    //Input Validation
    assert(argc > 1);

    char solution[MAXENTRIES][MAXENTRIES];

    if (0 == strcmp(argv[1], "data1")) {
        FILE *data1 = fopen(argv[1], "r");
        if (data1 == NULL) {
            fprintf(stderr, "Failed to open file\n");
            exit(1);
        }
        FILE *solution1 = fopen(argv[1], "r");
        if (solution1 == NULL) {
            fprintf(stderr, "Failed to open file\n");
            exit(1);
        }
        for (int i = 0; i < 44; i++) {
            for (int j = 0; j < 44; j++) {
                fscanf(solution1, "%c", &solution[i][j]);
            }
        }

        for (int k = 0; k < 44; k++) {
            for (int i = 0; i < 44; i++) {
                printf("%c", solution[k][i]);
            }
            printf("\n");
        }
        fclose(data1);
        fclose(solution1);
    } else if (0 == strcmp(argv[1], "data2")) {
        /*FILE *data2 = fopen(argv[1], "r");
        if (data2 == NULL) {
            fprintf(stderr, "Failed to open file\n");
            exit(1);
        }*/
        FILE *solution2 = fopen(argv[1], "r");
        if (solution2 == NULL) {
            fprintf(stderr, "Failed to open file\n");
            exit(1);
        }
        for (int i = 0; i < 35; i++) {
            for (int j = 0; j < 35; j++) {
                fscanf(solution2, "%c", &solution[i][j]);
            }
        }

        for (int k = 0; k < 35; k++) {
            for (int i = 0; i < 35; i++) {
                printf("%c", solution[k][i]);
            }
        }
        /*fclose(data2);*/
        fclose(solution2);
    } else if (0 == strcmp(argv[1], "data3")) {
        FILE *data3 = fopen(argv[1], "r");
        if (data3 == NULL) {
            fprintf(stderr, "Failed to open file\n");
            exit(1);
        }
        FILE *solution3 = fopen(argv[1], "r");
        if (solution3 == NULL) {
            fprintf(stderr, "Failed to open file\n");
            exit(1);
        }
        for (int i = 0; i < 31; i++) {
            for (int j = 0; j < 31; j++) {
                fscanf(solution3, "%c", &solution[i][j]);
            }
        }

        for (int k = 0; k < 31; k++) {
            for (int i = 0; i < 31; i++) {
                printf("%c", solution[k][i]);
            }
        }
        fclose(data3);
        fclose(solution3);
    }

    /*//DEBUG Statement
    printf("This will print if assertion is true");

    char firstLine[MAXENTRIES];

    fgets(firstLine, MAXENTRIES, myFile);

    //DEBUG: Used to see what is put in firstLine by fgets function.
    printf("%s\n", firstLine);

    //This will be used to create 2D array size later
    size_t numberofElementsWithSpaces = strlen(firstLine);

    //DEBUG Statement
    printf("Length of first line is: %zu\n", numberofElementsWithSpaces);

    char ArrayWithoutSpaces[(numberofElementsWithSpaces - 1) / 2][(numberofElementsWithSpaces - 1) / 2];

    for (int i = 0; i < (numberofElementsWithSpaces - 1) / 2; i++) {
        for (int j = 0; j < (numberofElementsWithSpaces - 1) / 2; j++) {
            fscanf(myFile, "%c", &ArrayWithoutSpaces[i][j]);
        }
    }

    for (int k = 0; k < (numberofElementsWithSpaces - 1) / 2; k++) {
        for (int i = 0; i < (numberofElementsWithSpaces - 1) / 2; i++) {
            printf("%c", ArrayWithoutSpaces[k][i]);
        }
        printf("\n");
    }*/

    return 0;
}

