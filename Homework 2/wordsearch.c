#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(int argc, char *argv[]) {

    FILE *myFile = fopen(argv[1], "r");
    if (myFile == NULL) {
        fprintf(stderr, "Failed to open file\n");
        exit(1);
    }

    //Input Validation
    assert(argc > 1);

    //DEBUG Statement
    printf("This will print if assertion is true");
    return 0;
}

