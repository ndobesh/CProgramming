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
};

//Next 4 structs contain operationCode values.
struct inputOutput {
    const int READ;
    const int WRIT;
    const int PRNT;
};

struct loadStore {
    const int LOAD;
    const int STOR;
    const int SET;
};

struct arithmetic {
    const int ADD;
    const int SUB;
    const int DIV;
    const int MULT;
    const int MOD;
};

struct control {
    const int BRAN;
    const int BRNG;
    const int BRZR;
    const int HALT;
};


void compile(void);

void execute(void);

void printMemory(void);

void initialize(int, char *);

int main(int argc, char *argv[]) {
    initialize(argc, argv);
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
//TODO: Flesh out
void printMemory(void) {

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
        } else if (0 == strcmp(&argv[1], "prog2")) {
            FILE *prog2 = fopen(&argv[1], "r");
            if (prog2 == NULL) {
                fprintf(stderr, "Failed to open file\n");
                exit(1);
            }
        }
    }

}

