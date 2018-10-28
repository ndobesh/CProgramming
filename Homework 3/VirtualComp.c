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

struct Files {
    FILE *prog1;
    FILE *prog2;
    FILE *prog3;
    FILE *noHalt;
    FILE *undefinedUse;
    FILE *CEunknownCommand;
    FILE *CEwordOverflow;
    FILE *divideZero;
    FILE *segFault;
    FILE *unknownChar;
    FILE *RTunknownCommand;
    FILE *RTwordOverflow;
    int whichFile;
    char *buffer;
} structfiles;


void compile(void);

void execute(void);

void printMemory(void);

void initialize(int, char *);

void closure(void);

int main(int argc, char *argv[]) {
    printf("argv: %s\n", argv[1]);
    char *program = argv[1];
    printf("program used: %s\n", program);
    initialize(argc, program);
    printf("Buffer from file: %s", structfiles.buffer);
    //DEBUG STATEMENT: see if initialization worked
    printf("Initialization complete!\n");
    printf("whichFile: %d", structfiles.whichFile);

    compile();
    //Temp disabled for debugging purposes.
    /*execute();*/

    closure();
    /*//DEBUG STATEMENT: close FILE(s) that was opened
    printf("\nClosure Complete!\nGoodbye!\n");*/
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

//Displays the values of each register and memory contents.
void printMemory(void) {
    printf("\nREGISTERS:\naccumulator\t\t\t%+.4d", structregisters.accumalator);
    printf("\ninstructionCounter\t\t\t% .2d", structregisters.InstructionCounter);
    printf("\ninstructionRegister\t\t\t%+.4d", structregisters.InstructionRegister);
    printf("\noperationCode\t\t\t\t% .2d", structregisters.OperationCode);
    printf("\noperand\t\t\t\t% .2d", structregisters.Operand);
    printf("\nMEMORY:\n");
    printf("\t0\t1\t2\t3\t4\t5\t6\t7\t8\t9");
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

//Opens files
void initialize(int argc, char *program) {
    //Assigning values to struct members.
    struct registers structregisters = {0, 0, 0, 0, 0, {0}};
    struct inputOutput structinputOutput = {10, 11, 12};
    struct loadStore structloadStore = {20, 21, 22};
    struct arithmetic structarithmetic = {30, 31, 32, 33, 34};
    struct control structcontrol = {40, 41, 42, 99};

    //Open each file to be used in program with "read" permission
    assert(argc > 1);
    if (0 == strcmp(program, "prog1")) {
        structfiles.prog1 = fopen(program, "r");
        structfiles.whichFile = 1;
        /*fread(structfiles.buffer, 1, 1, structfiles.prog1);*/
        if (structfiles.prog1 == NULL) {
            fprintf(stderr, "Failed to open file\n");
            exit(1);
        }
    } else if (0 == strcmp(program, "prog2")) {
        structfiles.prog2 = fopen(program, "r");
        structfiles.whichFile = 2;
        if (structfiles.prog2 == NULL) {
            fprintf(stderr, "Failed to open file\n");
            exit(1);
        }
    } else if (0 == strcmp(program, "prog3")) {
        structfiles.prog3 = fopen(program, "r");
        structfiles.whichFile = 3;
        if (structfiles.prog3 == NULL) {
            fprintf(stderr, "Failed to open file\n");
            exit(1);
        }
    } else if (0 == strcmp(program, "ce_no_halt")) {
        structfiles.noHalt = fopen(program, "r");
        structfiles.whichFile = 4;
        if (structfiles.noHalt == NULL) {
            fprintf(stderr, "Failed to open file\n");
            exit(1);
        }
    } else if (0 == strcmp(program, "ce_undefined_use")) {
        structfiles.undefinedUse = fopen(program, "r");
        structfiles.whichFile = 5;
        if (structfiles.undefinedUse == NULL) {
            fprintf(stderr, "Failed to open file\n");
            exit(1);
        }
    } else if (0 == strcmp(program, "ce_unknown_command")) {
        structfiles.CEunknownCommand = fopen(program, "r");
        structfiles.whichFile = 6;
        if (structfiles.CEunknownCommand == NULL) {
            fprintf(stderr, "Failed to open file\n");
            exit(1);
        }
    } else if (0 == strcmp(program, "ce_word_overflow")) {
        structfiles.CEwordOverflow = fopen(program, "r");
        structfiles.whichFile = 7;
        if (structfiles.CEwordOverflow == NULL) {
            fprintf(stderr, "Failed to open file\n");
            exit(1);
        }
    } else if (0 == strcmp(program, "rt_divide_by_zero")) {
        structfiles.divideZero = fopen(program, "r");
        structfiles.whichFile = 8;
        if (structfiles.divideZero == NULL) {
            fprintf(stderr, "Failed to open file\n");
            exit(1);
        }
    } else if (0 == strcmp(program, "rt_seg_fault")) {
        structfiles.segFault = fopen(program, "r");
        structfiles.whichFile = 9;
        if (structfiles.segFault == NULL) {
            fprintf(stderr, "Failed to open file\n");
            exit(1);
        }
    } else if (0 == strcmp(program, "rt_unknown_char")) {
        structfiles.unknownChar = fopen(program, "r");
        structfiles.whichFile = 10;
        if (structfiles.unknownChar == NULL) {
            fprintf(stderr, "Failed to open file\n");
            exit(1);
        }
    } else if (0 == strcmp(program, "rt_unknown_command")) {
        structfiles.RTunknownCommand = fopen(program, "r");
        structfiles.whichFile = 11;
        if (structfiles.RTunknownCommand == NULL) {
            fprintf(stderr, "Failed to open file\n");
            exit(1);
        }
    } else if (0 == strcmp(program, "rt_word_overflow")) {
        structfiles.RTwordOverflow = fopen(program, "r");
        structfiles.whichFile = 12;
        if (structfiles.RTwordOverflow == NULL) {
            fprintf(stderr, "Failed to open file\n");
            exit(1);
        }
    } else
        exit(1);
}

void closure(void) {
    switch (structfiles.whichFile) {
        case 1:
            fclose(structfiles.prog1);
            break;
        case 2:
            fclose(structfiles.prog2);
            break;
        case 3:
            fclose(structfiles.prog3);
            break;
        case 4:
            fclose(structfiles.noHalt);
            break;
        case 5:
            fclose(structfiles.undefinedUse);
            break;
        case 6:
            fclose(structfiles.CEunknownCommand);
            break;
        case 7:
            fclose(structfiles.CEwordOverflow);
            break;
        case 8:
            fclose(structfiles.divideZero);
            break;
        case 9:
            fclose(structfiles.segFault);
            break;
        case 10:
            fclose(structfiles.unknownChar);
            break;
        case 11:
            fclose(structfiles.RTunknownCommand);
            break;
        case 12:
            fclose(structfiles.RTwordOverflow);
            break;
        default:
            fprintf(stderr, "Failed to close file");
            exit(1);
    }
}

