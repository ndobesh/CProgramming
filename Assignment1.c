#include <stdlib.h>
#include <stdio.h>
#include <time.h>

char operator(void);

int randValue1(int);

int randValue2(int);

void generate_question(void);

void answer_question(int);

void print_response(void);

int main(void) {
    int questions;
    int difficulty;

    srand((unsigned int) time(NULL));

    /*TODO: Validate for non integer values entered
     * To do that, caputre the return value of scanf */

    do {
        printf("How many questions for this test (1 - 20)? ");
        scanf("%d", &questions);
    } while (questions < 1 || questions > 20);

    do {
        printf("Select difficulty (1 - 4): ");
        scanf("%d", &difficulty);
    } while (difficulty < 1 || difficulty > 4);


    /* DEBUG: make sure the inputted values are within bounds */
    printf("The amount of questions submitted is: %d\n", questions);
    printf("The difficulty selected is: %d\n", difficulty);

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
    int value1 = 0;
    int modulo = 0;
    int offset = 1;

    switch (n) {
        case 1:
            modulo = 10;
            break;
        case 2:
            modulo = 50;
            break;
        case 3:
            modulo = 100;
            break;
        case 4:
            /*To make the range from -100 to 100, make the max double than expected and subtract 100.
             * the end result will be 100 to 100 instead of 0 to 200. (value1 = rand() % 200 - 100; */
            modulo = 200;
            offset = -100;
            break;
        default:
            printf("ERROR: Something went wrong in randValue1 function");
    }

    value1 = rand() % modulo + offset;

    return value1;
}

int randValue2(int n) {
    int value2;
    int modulo = 0;
    int offset = 1;

    /*Section of code will repeat if value2 is 0. This will will avoid the divide by 0 case.*/
    do {
        switch (n) {
            case 1:
                modulo = 10;
                break;
            case 2:
                modulo = 50;
                break;
            case 3:
                modulo = 100;
                break;
            case 4:
                /*To make the range from -100 to 100, make the max double than expected and subtract 100.
                 * the end result will be 100 to 100 instead of 0 to 200. (value1 = rand() % 200 - 100; */
                modulo = 200;
                offset = -100;
                break;
            default:
                printf("ERROR: Something went wrong in randValue1 function");
        }
        value2 = rand() % modulo + offset;
    } while (value2 != 0);

    return value2;
}

void generate_question(void) {

}

void answer_question(int rightAnswer) {

}

void print_response(int n) {
    /*Will need value passed in from answer_question(int)*/

    /*Different switch statement for either right or wrong response*/
    /*Right response switch statement*/
    int randRightResponse = rand() % 3 + 1;
    switch (randRightResponse) {
        case 1:
            printf("Nice!");
            break;
        case 2:
            printf("Good job!");
            break;
        case 3:
            printf("You're right!");
            break;
        default:
            printf("ERROR: Something went wrong.");
    }
}
