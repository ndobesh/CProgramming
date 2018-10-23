#include <stdio.h>


//TODO: Put in comments for each variable in structs
struct registers {
    int accumalator;
    int InstructionCounter;
    int InstructionRegister;
    int OperationCode;
    int Operand;
    int memory[100];
};

struct inputOutput {
    const int read = 10;
    const int writ = 11;
    const int prnt = 12;
};

struct loadStore {
    const int load = 20;
    const int stor = 21;
    const int set = 22;
};

struct arithmetic {
    const int add = 30;
    const int sub = 31;
    const int div = 32;
    const int mult = 33;
    const int mod = 34;
};

struct control {
    const int bran = 40;
    const int brng = 41;
    const int brzr = 42;
    const int halt = 99;
};


void compile(void);

void execute(void);

void printMemory(void);

void initialize(void);

int main(void) {
    initialize();
    compile();
    execute();
    return 0;
}

//TODO: change  void if necessary
//TODO: Flesh out
void compile(void) {

}

//TODO: change  void if necessary
//Flesh out
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
void initialize(void) {

}

