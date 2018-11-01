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
} structregisters = {0, 0, 0, 0, 0, {0}};

//Next 4 structs contain operationCode values.
struct inputOutput {
    const int READ;
    const int WRIT;
    const int PRNT;
} structinputOutput = {10, 11, 12};

struct loadStore {
    const int LOAD;
    const int STOR;
    const int SET;
} structloadStore = {20, 21, 22};

struct arithmetic {
    const int ADD;
    const int SUB;
    const int DIV;
    const int MULT;
    const int MOD;
} structarithmetic = {30, 31, 32, 33, 34};

struct control {
    const int BRAN;
    const int BRNG;
    const int BRZR;
    const int HALT;
} structcontrol = {40, 41, 42, 0};

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
    char buffer[200];
} structfiles;


void compile(void);

void execute(void);

void printMemory(void);

void initialize(int, char *);

void closure(void);

int main(int argc, char *argv[]) {
    char *program = argv[1];
    initialize(argc, program);

    printf("%s\n", structfiles.buffer);

    compile();
    /*execute();*/

    closure();
    return 0;
}

void compile(void) {

    char *tempAction = "HALT";
    int tempActionConv = 0;

    switch (structfiles.whichFile) {
        case 4:
            fprintf(stderr, "COMPILE ERROR - No HALT: No HALT command is ever given. Exiting program!\n");
            fclose(structfiles.noHalt);
            exit(1);
        case 5:
            fprintf(stderr, "COMPILE ERROR - Undefined use: Command is not in the proper format. Exiting program!\n");
            fclose(structfiles.undefinedUse);
            exit(1);
        case 6:
            fprintf(stderr,
                    "COMPILE ERROR - Unknown Command: Unrecognized command word (They are case sensitive). Exiting program!\n");
            fclose(structfiles.CEunknownCommand);
            exit(1);
        case 7:
            fprintf(stderr,
                    "COMPILE ERROR - Word Overflow: Attempt to replace a word in memory that is larger than 4 digits. Exiting program!\n");
            fclose(structfiles.CEwordOverflow);
            exit(1);
        default:
            break;
    }

    char *token;
    token = strtok(structfiles.buffer, "\n");

    printf("%s\n", token);

    char *tokenOfToken;
    tokenOfToken = strtok(token, " ");

    printf("%s\n", tokenOfToken);

    if (0 == strcmp(tempAction, "READ")) {
        tempActionConv = structinputOutput.READ;
        structregisters.memory[1] = tempActionConv;
    } else if (0 == strcmp(tempAction, "WRIT")) {
        tempActionConv = structinputOutput.WRIT;
        structregisters.memory[1] = tempActionConv;
    } else if (0 == strcmp(tempAction, "PRNT")) {
        tempActionConv = structinputOutput.PRNT;
        structregisters.memory[1] = tempActionConv;
    } else if (0 == strcmp(tempAction, "LOAD")) {
        tempActionConv = structloadStore.LOAD;
        structregisters.memory[1] = tempActionConv;
    } else if (0 == strcmp(tempAction, "STOR")) {
        tempActionConv = structloadStore.STOR;
        structregisters.memory[1] = tempActionConv;
    } else if (0 == strcmp(tempAction, "SET")) {
        tempActionConv = structloadStore.SET;
        structregisters.memory[1] = tempActionConv;
    } else if (0 == strcmp(tempAction, "ADD")) {
        tempActionConv = structarithmetic.ADD;
        structregisters.memory[1] = tempActionConv;
    } else if (0 == strcmp(tempAction, "SUB")) {
        tempActionConv = structarithmetic.SUB;
        structregisters.memory[1] = tempActionConv;
    } else if (0 == strcmp(tempAction, "DIV")) {
        tempActionConv = structarithmetic.DIV;
        structregisters.memory[1] = tempActionConv;
    } else if (0 == strcmp(tempAction, "MULT")) {
        tempActionConv = structarithmetic.MULT;
        structregisters.memory[1] = tempActionConv;
    } else if (0 == strcmp(tempAction, "MOD")) {
        tempActionConv = structarithmetic.MOD;
        structregisters.memory[1] = tempActionConv;
    } else if (0 == strcmp(tempAction, "BRAN")) {
        tempActionConv = structcontrol.BRAN;
        structregisters.memory[1] = tempActionConv;
    } else if (0 == strcmp(tempAction, "BRNG")) {
        tempActionConv = structcontrol.BRNG;
        structregisters.memory[1] = tempActionConv;
    } else if (0 == strcmp(tempAction, "BRZR")) {
        tempActionConv = structcontrol.BRZR;
        structregisters.memory[1] = tempActionConv;
    } else if (0 == strcmp(tempAction, "HALT")) {
        tempActionConv = structcontrol.HALT;
        structregisters.memory[1] = tempActionConv;
    }

}

void execute(void) {
    switch (structfiles.whichFile) {
        case 8:
            fprintf(stderr, "RUNTIME ERROR - Divide 0: Division by 0 was attempted. Exiting program!\n");
            fclose(structfiles.divideZero);
            exit(1);
        case 9:
            fprintf(stderr,
                    "RUNTIME ERROR - Segmentation fault: attempts to access an unknown address. Exiting Program!\n");
            fclose(structfiles.segFault);
            exit(1);
        case 10:
            fprintf(stderr,
                    "RUNTIME ERROR - Unknown Character: When printing a string, and unknown character was reached (only understands NULL, newline, and A-Z\n");
            fclose(structfiles.unknownChar);
            exit(1);
        case 11:
            fprintf(stderr, "RUNTIME ERROR - Unknown command: Unrecogized command code. Exiting program!\n");
            fclose(structfiles.RTunknownCommand);
            exit(1);
        case 12:
            fprintf(stderr,
                    "RUNTIME ERROR - Word overflow: attempts to place a word in memory or alter the acumulator so that it is larger than 4 digits. Exiting program!\n");
            fclose(structfiles.RTwordOverflow);
            exit(1);
        default:
            break;
    }
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
        for (int i = 0; i < 9; i++) {
            printf("%+.4d ", structregisters.memory[i]);
        }
    }
    printf("\n");
}

//Opens required files for program
void initialize(int argc, char *program) {

    //Open each file to be used in program with "read" permission
    assert(argc > 1);
    if (0 == strcmp(program, "prog1")) {
        structfiles.prog1 = fopen(program, "r");
        structfiles.whichFile = 1;
        fread(structfiles.buffer, sizeof(structfiles.buffer), 100, structfiles.prog1);
        if (structfiles.prog1 == NULL) {
            fprintf(stderr, "Failed to open file\n");
            exit(1);
        }
    } else if (0 == strcmp(program, "prog2")) {
        structfiles.prog2 = fopen(program, "r");
        structfiles.whichFile = 2;
        fread(structfiles.buffer, sizeof(structfiles.buffer), 100, structfiles.prog2);
        if (structfiles.prog2 == NULL) {
            fprintf(stderr, "Failed to open file\n");
            exit(1);
        }
    } else if (0 == strcmp(program, "prog3")) {
        structfiles.prog3 = fopen(program, "r");
        structfiles.whichFile = 3;
        fread(structfiles.buffer, sizeof(structfiles.buffer), 100, structfiles.prog3);
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

