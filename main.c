#include <stdbool.h>
#include <stdio.h>

#define STACK_SIZE 256
static int stack[STACK_SIZE];

typedef enum {
   PSH,
   ADD,
   POP,
   HLT
} InstructionSet;

// I want to add the added value to the stack.
const int instructions[] = {
    PSH, 5,
    PSH, 6,
    ADD,
    POP,
    HLT
};

typedef enum{
  A, B, C, D, E, F,
  SP,
  IP,
  REGISTER_SIZE
} Registers;

static int registers[REGISTER_SIZE];

#define IP (registers[IP])
#define SP (registers[SP])
#define FETCH (instructions[IP])

bool running = true;

void print_stack(){
  printf("Stack Log:\n");
  for(int i = 0; i < SP; i++){
    printf("%d\n", stack[i]);
  }
  printf("\n");
}

void print_registers(){ 
  printf("Register dump: \n");
  for(int i = 0; i < REGISTER_SIZE; i++){
    printf("REG: %d\n", registers[i]);
  }
  printf("\n");
}

void eval(int instr){
  switch(instr){
    case HLT: {
      running = false;
      print_stack();
      print_registers();
      break;
    }
    case PSH: {
      SP = SP + 1;
      IP = IP + 1;
      stack[SP] = instructions[IP]; // We push here because the value is right after the PSH. 

      printf("PUSHING TO STACK: %d\n", instructions[IP]);
                                 
      break;
    }
    case POP: {
      SP = SP - 1;
      return;
    } 
    case ADD: {
      // Pop a and then pop b. Add them, psh to stack;
      registers[A] = stack[SP];
      SP = SP - 1;

      registers[B] = stack[SP];

      registers[C] = registers[B] + registers[A];
      printf("ADD: %d + %d\n", registers[B], registers[A]);

      printf("DEBUG: Reg[C], %d\n", registers[C]);
      stack[SP] = registers[C];
      printf("DEBUG: stack[SP], %d\n", stack[SP]);
      return;
    }
  }
}

int main(){
  SP = -1;
  while(running){
    eval(FETCH);
    IP = IP + 1;
  }
  
  return 0;
}
