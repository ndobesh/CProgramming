#include <stdlib.h>
#include <stdio.h>
#include <time.h>

char operator(void);

int randValue1(int);

int randValue2(int);

void generate_question(void);

void answer_question(void);

void print_response(void);

int main(void) {
    int questions;
    int value1;
    int value2;

    srand((unsigned int) time(NULL));

    printf("How many questions would you like to answer? ");
    scanf("%d", &questions);
    printf("The response submitted is: %d\n", questions);

    char Operator1 = operator();
    printf("Operator returned from function is: %c", Operator1);

    return 0;
}

char operator(void) {
    int randOperatorNum = rand() % 4 + 1;
    char randOperator = 0;
    printf("Random operator number generated is: %d\n", randOperatorNum);

    switch (randOperatorNum) {
        case 1:
            randOperator = '+';
            break;
        case 2:
            randOperator = '-';
            break;
        case 3:
            randOperator = '*';
            break;
        case 4:
            randOperator = '/';
            break;
        default:
            "ERROR: Invalid number.";

    }
    printf("Random Operator within operator() function: %c\n", randOperator);
    return randOperator;
}

int randValue1(int n) {

    return 0; /*to be changed*/
}

int randValue2(int n) {

    return 0; /*to be changed*/
}

void generate_question(void) {

}

void answer_question(void) {

}

void print_response(void) {

}
