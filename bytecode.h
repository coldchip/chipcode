#ifndef BYTECODE_H
#define BYTECODE_H

#include <string>
#include <iostream>
#include <vector>

using namespace std;

typedef enum {
	V_REG,
	V_ADDR,
	V_DEREF,
	V_REF,
	V_VALUE,
	V_LABEL,
	V_NONE
} VType;

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
	OP_SETSP, // set current stack pointer to reg
	OP_GETSP, // get current stack pointer to reg
	OP_MOVDR, // derefrence pointer from a reg to a reg
	OP_NOP  // do nothing
} OPCode;

typedef struct _Instruction {
	OPCode op;
	VType ltype;
	string left;
	VType rtype;
	string right;
} Instruction;

typedef struct _Procedure {
	string name;
	vector<Instruction> instructions;
} Procedure;

class ByteCode {
	public:
		ByteCode();
		void SetCurrentWorkingProcedure(string name);
		string GetCurrentWorkingProcedure();
		void Emit(OPCode op, VType ltype, string left, VType rtype, string right);
		static string GetInstructionAsString(OPCode op);
		static string GetVTypeAsString(VType type);
		void Dump();
		vector<Procedure> Build();
		~ByteCode();
	private:
		string currentProcedure;
		vector<Procedure> program;

		Procedure &GetProcedure(string name);
};

#endif