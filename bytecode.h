#ifndef BYTECODE_H
#define BYTECODE_H

#include <vector>

using namespace std;

typedef struct _Instruction {
	
} Instruction;

typedef struct _Procedure {
	vector<Instruction> instructions;
} Procedure;

class ByteCode {
	public:
		ByteCode();
		~ByteCode();
	private:
		vector<Procedure> program;
};

#endif