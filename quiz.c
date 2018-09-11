#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/*TODO: Confirm I don't need this function anymore*/
/*char operator(void);*/

int randValue1(int);

int randValue2(int);

int generate_question(int, int);

int answer_question(int);

void print_response(int, int);

int main(void) {
    int questions;
    int difficulty;

    srand((unsigned int) time(NULL));

    /*TODO: Validate for non integer values entered
     * To do that, capture the return value of scanf */

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

    /*TODO: Confirm I don't need this function anymore*/
    /*char Operator1 = operator();
    printf("Operator returned from function is: %c", Operator1);*/

    return 0;
}

/*TODO: Confirm I don't need this function anymore*/
/*char operator(void) {
    int randOperatorNum = rand() % 4 + 1;
    char randOperator = 0;

    *//*DEBUG: Make sure the rand num is generated properly*//*
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
}*/

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

int randValue2(int diff) {
    int value2;
    int modulo = 0;
    int offset = 1;

    /*Section of code will repeat if value2 is 0. This will will avoid the divide by 0 case.*/
    do {
        switch (diff) {
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

int generate_question(int questions, int difficulty) {
    int val1 = randValue1(difficulty);
    int val2 = randValue2(difficulty);
    /*char op = operator();*/
    int rightAnswer = 0;

    int randOperatorNum = rand() % 4 + 1;

    switch (randOperatorNum) {
        case 1:
            rightAnswer = val1 + val2;
            printf("Question %d: %d + %d =", questions, val1, val2);
            break;
        case 2:
            rightAnswer = val1 - val2;
            printf("Question %d: %d - %d =", questions, val1, val2);
            break;
        case 3:
            rightAnswer = val1 * val2;
            printf("Question %d: %d * %d =", questions, val1, val2);
            break;
        case 4:
            rightAnswer = val1 / val2;
            printf("Question %d: %d / %d =", questions, val1, val2);
            break;
        default:
            printf("ERROR: Something went wrong in generate_question function");

    }

    return rightAnswer;
}

int answer_question(int rightAnswer) {
    int generatedAnswer = rightAnswer;
    int userAnswer = 0;
    int userCorrect = 0;

    printf("Enter Answer: ");
    scanf("%d", &userAnswer);

    if (userAnswer == generatedAnswer)
        userCorrect = 0;
    else
        userCorrect = 1;


    return userCorrect;
}

void print_response(int n, int rightAnswer) {
    /*Will need value passed in from answer_question(int)*/

    /*Different switch statement for either right or wrong response*/
    /*Right response switch statement*/
    if (n == 0) {
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
    } else {
        printf("Sorry!");
        printf("The correct answer was %d", rightAnswer);
    }


}
