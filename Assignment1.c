

char operator(void);

int main(void) {
    int questions;

    srand(time(NULL));

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
    printf("Random operator nummber generated is: %d\n", randOperatorNum);

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