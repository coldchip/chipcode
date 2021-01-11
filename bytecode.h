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
	OP_CALL,
	OP_MOV
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
		void Emit(OPCode op, string left, string right);
		void Dump();
		vector<Procedure> Build();
		~ByteCode();
	private:
		string currentProcedure;
		vector<Procedure> program;

		Procedure &GetProcedure(string name);
};

#endif