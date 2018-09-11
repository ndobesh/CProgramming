#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int randValue1(int);

int randValue2(int);

int generate_question(int, int);

int answer_question(int);

void print_response(int, int);

void discard_junk(void);

int main(void) {
    int questions;
    int difficulty;
    int resultReturn;
    int userCorrectReturn;
    int tallyCorrect = 0;
    int n = 0; /*matching items caught from scan*/

    srand((unsigned int) time(NULL));

    do {
        printf("How many questions for this test (1 - 20)? ");
        n = scanf("%d", &questions);
        if (n != 1)
            discard_junk();
    } while (n != 1 || questions < 1 || questions > 20);

    do {
        printf("Select difficulty (1 - 4): ");
        n = scanf("%d", &difficulty);
        if (n != 1)
            discard_junk();
    } while (n != 1 || difficulty < 1 || difficulty > 4);

    for (int i = 1; i <= questions; i++) {
        resultReturn = generate_question(i, difficulty);
        userCorrectReturn = answer_question(resultReturn);
        if (userCorrectReturn == 0)
            tallyCorrect++;
        print_response(userCorrectReturn, resultReturn);
    }

    printf("Your score was %d/%d\n", tallyCorrect, questions);

    return 0;
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
    } while (value2 == 0);

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
            printf("Question %d: %d + %d =\n", questions, val1, val2);
            break;
        case 2:
            rightAnswer = val1 - val2;
            printf("Question %d: %d - %d =\n", questions, val1, val2);
            break;
        case 3:
            rightAnswer = val1 * val2;
            printf("Question %d: %d * %d =\n", questions, val1, val2);
            break;
        case 4:
            rightAnswer = val1 / val2;
            printf("Question %d: %d / %d =\n", questions, val1, val2);
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
                printf("Nice!\n");
                break;
            case 2:
                printf("Good job!\n");
                break;
            case 3:
                printf("You're right!\n");
                break;
            default:
                printf("ERROR: Something went wrong.\n");
        }
    } else {
        int randWrongResponse = rand() % 3 + 1;
        switch (randWrongResponse) {
            case 1:
                printf("Sorry!\n");
                break;
            case 2:
                printf("Not quite!\n");
                break;
            case 3:
                printf("Nope!\n");
                break;
            default:
                printf("ERROR: Something went wrong with wrong response");
        }
        printf("The correct answer was %d\n", rightAnswer);
    }


}

/*Used for cleaning the input buffer when an invalid value is entered
 * Idea for this validation came from:
 *https://stackoverflow.com/questions/31633005/validate-the-type-of-input-in-a-do-while-loop-c */
void discard_junk(void) {
    char c;
    while ((c = (char) getchar()) != '\n' && c != EOF);
}
