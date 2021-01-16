#ifndef MAIN
#define MAIN

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

typedef enum {
	OP_POP, // pop from stack
	OP_PUSH, // push to stack
	OP_ADD, // add among regs
	OP_SUB, // sub among regs
	OP_MUL, // mul among regs
	OP_DIV, // div among regs
	OP_CALL, // call procedure
	OP_MOV, // move data to address
	OP_CMP, // compare among regs
	OP_JMP, // jump to procedure
	OP_JE, // jump to procedure if equals
	OP_JNE, // jump to procedure if NOT equals
	OP_JLZ, // jump to procedure if lesser than
	OP_JGZ, // jump to procedure if more than
	OP_SETGT, // set register to 1 if last comparision result is more than
	OP_SETLT,  // set register to 1 if last comparision result is less than
	OP_NOP,  // do nothing
	OP_END  // end procedure
} OPCode;

void dump_instructions();

#endif