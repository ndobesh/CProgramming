#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <memory.h>


struct registers {
    int accumalator; //register that operations are performed upon.
    int InstructionCounter; //register that stores the address of the current instruction to be executed
    int InstructionRegister; //register that stores the current instruction fetched from VM memory.
    int OperationCode; // register that stores the opeation to be done (i.e. READ, BRAN, ADD, etc.)
    int Operand; // register that stores the memory address to be used in instruction.
    int memory[100]; // Array used as memory of VM wich each location having 4 digit integers.
} structregisters;

//Next 4 structs contain operationCode values.
struct inputOutput {
    const int READ;
    const int WRIT;
    const int PRNT;
} structinputOutput;

struct loadStore {
    const int LOAD;
    const int STOR;
    const int SET;
} structloadStore;

struct arithmetic {
    const int ADD;
    const int SUB;
    const int DIV;
    const int MULT;
    const int MOD;
} structarithmetic;

struct control {
    const int BRAN;
    const int BRNG;
    const int BRZR;
    const int HALT;
} structcontrol;


void compile(void);

void execute(void);

void printMemory(void);

void initialize(int, char *);

int main(int argc, char *argv[]) {
    initialize(argc, *argv);
    //DEBUG STATEMENT: see if initialization worked
    //printf("Initialization complete!\n");

    compile();
    execute();
    return 0;
}

//TODO: change  void if necessary
//TODO: Flesh out
void compile(void) {

}

//TODO: change  void if necessary
//TODO: Flesh out
void execute(void) {
    printMemory();
}

//TODO: change  void if necessary
void printMemory(void) {
    printf("\nREGISTERS:\naccumulator\t\t\t\t\t%+.4d", structregisters.accumalator);
    printf("\ninstructionCounter\t\t\t% .2d", structregisters.InstructionCounter);
    printf("\ninstructionRegister\t\t\t%+.4d", structregisters.InstructionRegister);
    printf("\noperationCode\t\t\t\t% .2d", structregisters.OperationCode);
    printf("\noperand\t\t\t\t\t\t% .2d", structregisters.Operand);
    printf("\nMEMORY:\n");
    printf("   \t0\t\t1\t  2\t\t3\t  4\t\t 5\t  6\t\t 7\t  8\t\t 9");
    int column = 0;
    for (int j = 0; j <= 9; j++) {
        printf("\n%d ", column);
        column += 10;

        if (j == 0) {
            printf(" ");
        }
        for (int i = 0; i < 10; i++) {
            printf("%+.4d ", structregisters.memory[i]);
        }
    }
}

//TODO: change  void if necessary
//TODO: Flesh out
//Opens files
void initialize(int argc, char *argv) {
    //Assigning values to struct members.
    struct registers structregisters = {0, 0, 0, 0, 0, 0, 0};
    struct inputOutput structinputOutput = {10, 11, 12};
    struct loadStore structloadStore = {20, 21, 22};
    struct arithmetic structarithmetic = {30, 31, 32, 33, 34};
    struct control structcontrol = {40, 41, 42, 99};

    //Open each file to be used in program with "read" permission
    assert(argc > 1);
    if (0 == strcmp(&argv[1], "prog1")) {
        FILE *prog1 = fopen(&argv[1], "r");
        if (prog1 == NULL) {
            fprintf(stderr, "Failed to open file\n");
            exit(1);
        }
    } else if (0 == strcmp(&argv[1], "prog2")) {
        FILE *prog2 = fopen(&argv[1], "r");
        if (prog2 == NULL) {
            fprintf(stderr, "Failed to open file\n");
            exit(1);
        }
    } else if (0 == strcmp(&argv[1], "prog3")) {
        FILE *prog3 = fopen(&argv[1], "r");
        if (prog3 == NULL) {
            fprintf(stderr, "Failed to open file\n");
            exit(1);
        }
    } else if (0 == strcmp(&argv[1], "ce_no_halt")) {
        FILE *noHalt = fopen(&argv[1], "r");
        if (noHalt == NULL) {
            fprintf(stderr, "Failed to open file\n");
            exit(1);
        }
    } else if (0 == strcmp(&argv[1], "ce_undefined_use")) {
        FILE *undefinedUse = fopen(&argv[1], "r");
        if (undefinedUse == NULL) {
            fprintf(stderr, "Failed to open file\n");
            exit(1);
        }
    } else if (0 == strcmp(&argv[1], "ce_unknown_command")) {
        FILE *unknownCommand = fopen(&argv[1], "r");
        if (unknownCommand == NULL) {
            fprintf(stderr, "Failed to open file\n");
            exit(1);
        }
    } else if (0 == strcmp(&argv[1], "ce_word_overflow")) {
        FILE *wordOverflow = fopen(&argv[1], "r");
        if (wordOverflow == NULL) {
            fprintf(stderr, "Failed to open file\n");
            exit(1);
        }
    } else if (0 == strcmp(&argv[1], "rt_divide_by_zero")) {
        FILE *divideZero = fopen(&argv[1], "r");
        if (divideZero == NULL) {
            fprintf(stderr, "Failed to open file\n");
            exit(1);
        }
    } else if (0 == strcmp(&argv[1], "ce_no_halt")) {
        FILE *noHalt = fopen(&argv[1], "r");
        if (noHalt == NULL) {
            fprintf(stderr, "Failed to open file\n");
            exit(1);
        }
    } else if (0 == strcmp(&argv[1], "rt_seg_fault")) {
        FILE *segFault = fopen(&argv[1], "r");
        if (segFault == NULL) {
            fprintf(stderr, "Failed to open file\n");
            exit(1);
        }
    } else if (0 == strcmp(&argv[1], "rt_unknown_char")) {
        FILE *unknownChar = fopen(&argv[1], "r");
        if (unknownChar == NULL) {
            fprintf(stderr, "Failed to open file\n");
            exit(1);
        }
    } else if (0 == strcmp(&argv[1], "rt_unknown_command")) {
        FILE *unknownCommand = fopen(&argv[1], "r");
        if (unknownCommand == NULL) {
            fprintf(stderr, "Failed to open file\n");
            exit(1);
        }
    } else if (0 == strcmp(&argv[1], "rt_word_overflow")) {
        FILE *wordOverflow = fopen(&argv[1], "r");
        if (wordOverflow == NULL) {
            fprintf(stderr, "Failed to open file\n");
            exit(1);
        }
    }
}

