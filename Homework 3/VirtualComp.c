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

//This struct contains the file pointers for each possible file used.
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

int concatenate(int, int);

void initialize(int, char *);

void closure(void);

int main(int argc, char *argv[]) {
    char *program = argv[1];
    initialize(argc, program);

    compile();
    execute();

    closure();
    return 0;
}

void compile(void) {


    //Handles all compile time error files
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


    char *token = strtok(structfiles.buffer, "\n");

    while (token != NULL) {
        char tempMemLoc[3];
        char tempOperation[4];
        char tempOperand[3];

        strcpy(tempMemLoc, strtok(token, " "));
        strcpy(tempOperation, strtok(NULL, " "));
        strcpy(tempOperand, strtok(NULL, " "));

        /*printf("tempMemLoc: %c\ntempOperation: %s\ntempOperand: %s\n", tempMemLoc[1], tempOperation, tempOperand);*/

        int memLoc = atoi(tempMemLoc);
        int operand = atoi(tempOperand);
        int tempActionConv = 0;

        if (0 == strcmp(tempOperation, "READ")) {
            tempActionConv = structinputOutput.READ;
            structregisters.memory[memLoc] = concatenate(tempActionConv, operand);
        } else if (0 == strcmp(tempOperation, "WRIT")) {
            tempActionConv = structinputOutput.WRIT;
            structregisters.memory[memLoc] = tempActionConv;
        } else if (0 == strcmp(tempOperation, "PRNT")) {
            tempActionConv = structinputOutput.PRNT;
            structregisters.memory[memLoc] = tempActionConv;
        } else if (0 == strcmp(tempOperation, "LOAD")) {
            tempActionConv = structloadStore.LOAD;
            structregisters.memory[memLoc] = tempActionConv;
        } else if (0 == strcmp(tempOperation, "STOR")) {
            tempActionConv = structloadStore.STOR;
            structregisters.memory[memLoc] = tempActionConv;
        } else if (0 == strcmp(tempOperation, "SET")) {
            tempActionConv = structloadStore.SET;
            structregisters.memory[memLoc] = tempActionConv;
        } else if (0 == strcmp(tempOperation, "ADD")) {
            tempActionConv = structarithmetic.ADD;
            structregisters.memory[memLoc] = tempActionConv;
        } else if (0 == strcmp(tempOperation, "SUB")) {
            tempActionConv = structarithmetic.SUB;
            structregisters.memory[memLoc] = tempActionConv;
        } else if (0 == strcmp(tempOperation, "DIV")) {
            tempActionConv = structarithmetic.DIV;
            structregisters.memory[memLoc] = tempActionConv;
        } else if (0 == strcmp(tempOperation, "MULT")) {
            tempActionConv = structarithmetic.MULT;
            structregisters.memory[memLoc] = tempActionConv;
        } else if (0 == strcmp(tempOperation, "MOD")) {
            tempActionConv = structarithmetic.MOD;
            structregisters.memory[memLoc] = tempActionConv;
        } else if (0 == strcmp(tempOperation, "BRAN")) {
            tempActionConv = structcontrol.BRAN;
            structregisters.memory[memLoc] = tempActionConv;
        } else if (0 == strcmp(tempOperation, "BRNG")) {
            tempActionConv = structcontrol.BRNG;
            structregisters.memory[memLoc] = tempActionConv;
        } else if (0 == strcmp(tempOperation, "BRZR")) {
            tempActionConv = structcontrol.BRZR;
            structregisters.memory[memLoc] = tempActionConv;
        } else if (0 == strcmp(tempOperation, "HALT")) {
            tempActionConv = structcontrol.HALT;
            structregisters.memory[memLoc] = tempActionConv;
        }
        token = strtok(NULL, "\n");
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
    printf("%8d%6d%6d%6d%6d%6d%6d%6d%6d%6d", 0, 1, 2, 3, 4, 5, 6, 7, 8, 9);

    for (int i = 0; i < 100; i += 10) {
        printf("\n%d", i);
        for (int j = 0; j < 10; j++) {
            printf(" %+.4d", structregisters.memory[j + i]);
        }
    }
    printf("\n");
}

//Function will take to int values and concatenate this together.
//E.X. x = 12 y = 34 -> z =1234
//Source: https://stackoverflow.com/questions/12700497/how-to-concatenate-two-integers-in-c
int concatenate(int x, int y) {
    int pow = 10;
    while (y >= pow)
        pow *= 10;
    return x * pow + y;
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

