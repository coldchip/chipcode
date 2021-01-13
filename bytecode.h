#ifndef BYTECODE_H
#define BYTECODE_H

#include <string>
#include <iostream>
#include <vector>

using namespace std;

typedef enum {
	OP_POP,
	OP_PUSH,
	OP_ADD,
	OP_SUB,
	OP_MUL,
	OP_DIV,
	OP_CALL,
	OP_MOV,
	OP_CMP,
	OP_JMP,
	OP_JE,
	OP_JNE,
	OP_JLZ,
	OP_JGZ
} OPCode;

typedef struct _Instruction {
	OPCode op;
	string left;
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
		void Emit(OPCode op, string left, string right);
		string GetInstructionAsString(OPCode op);
		void Dump();
		vector<Procedure> Build();
		~ByteCode();
	private:
		string currentProcedure;
		vector<Procedure> program;

		Procedure &GetProcedure(string name);
};

#endif