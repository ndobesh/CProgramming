#include <stdio.h>
#include <stdlib.h>

void initialize(void);

void closure(void);

int main(int argc, char *argv[]) {
    char *charPerLinePointer = argv[1];
    int charPerLine = atoi(charPerLinePointer);

    printf("%d", charPerLine);

    initialize();
    closure();
    return 0;
}

void initialize(void) {

}

void closure(void) {

}