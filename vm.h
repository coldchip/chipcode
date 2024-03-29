#ifndef VM_H
#define VM_H

#include "bytecode.h"
#include <cstring>
#include <vector>

using namespace std;

class VM {
	public:
		VM(vector<Procedure> program);
		Procedure &GetProcedure(string name);
		void Run(string name);
		void ExecProcedure(Procedure &proc, char *stack, int *reg, int fp, int sp);
		~VM();
	private:
		vector<Procedure> program;
};

#endif