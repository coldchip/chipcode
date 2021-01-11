#include "vm.h"

VM::VM(vector<Procedure> program) {
	this->program = program;
}

Procedure &VM::GetProcedure(string name) {
	for(Procedure &proc : this->program) {
		if(proc.name.compare(name) == 0) {
			return proc;
		}
	}

	throw string("unable to find procedure" + name);
}

void VM::Run(string name) {
	Procedure &proc = this->GetProcedure(name);
	this->ExecProcedure(proc);
}

void VM::ExecProcedure(Procedure &proc) {
	int reg[7];
	char stack[65535];
	int sp = 0;
	memset(stack, 0 , sizeof(stack));
	memset(reg, 0 , sizeof(reg));

	for(Instruction &ins : proc.instructions) {
		OPCode op = ins.op;
		string left = ins.left;
		string right = ins.right;
		switch(op) {
			case OP_PUSH: {
				if(this->IsReg(left)) {
					int i = this->GetRegIndex(left);
					*(int*)(stack + sp) = reg[i];
				} else if(this->IsAddress(left)) {
					int where = this->GetAddressIndex(left);
					int *a = (int*)(stack + where);
					*(int*)(stack + sp) = *a;
				} else {
					*(int*)(stack + sp) = stoi(left);
				}
				sp += 4;
			}
			break;
			case OP_POP: {
				sp -= 4;
				if(this->IsReg(left)) {
					int i = this->GetRegIndex(left);
					reg[i] = *(int*)(stack + sp);
				} else if(this->IsAddress(left)) {
					int where = this->GetAddressIndex(left);
					int *a = (int*)(stack + where);
					*a = *(int*)(stack + sp);
				} else {
					throw string("pop to a literal isn't allowed");
				}
			}
			break;
			case OP_ADD: {
				if(this->IsReg(left) && this->IsReg(right)) {
					int a = this->GetRegIndex(left);
					int b = this->GetRegIndex(right);
					reg[a] += reg[b];
				} else {
					throw string("add only can be done to regs");
				}
			}
			break;
			case OP_SUB: {
				if(this->IsReg(left) && this->IsReg(right)) {
					int a = this->GetRegIndex(left);
					int b = this->GetRegIndex(right);
					reg[a] -= reg[b];
				} else {
					throw string("add only can be done to regs");
				}
			}
			break;
			case OP_MUL: {
				if(this->IsReg(left) && this->IsReg(right)) {
					int a = this->GetRegIndex(left);
					int b = this->GetRegIndex(right);
					reg[a] *= reg[b];
				} else {
					throw string("add only can be done to regs");
				}
			}
			break;
			case OP_DIV: {
				if(this->IsReg(left) && this->IsReg(right)) {
					int a = this->GetRegIndex(left);
					int b = this->GetRegIndex(right);
					reg[a] /= reg[b];
				} else {
					throw string("add only can be done to regs");
				}
			}
			break;
			case OP_CALL: {
				if(left.compare("dbgregs") == 0) {
					printf("----- DUMP REGISTERS -----\n");
					printf("SP: %i\n", sp);
					printf("R0: %i\n", reg[0]);
					printf("R1: %i\n", reg[1]);
					printf("R2: %i\n", reg[2]);
					printf("R3: %i\n", reg[3]);
					printf("R4: %i\n", reg[4]);
					printf("R4: %i\n", reg[5]);
				} else if(left.compare("dbgstack") == 0) {
					printf("----- DUMP STACK -----\n");
					for(int i = 0; i < 256; i++) {
						if(i % 4 == 0) {
							printf("\n%i: ", i);
						}
						printf("%02x", *(stack + i) & 0xFF);
					}
					printf("\n");
				}
			}
			break;
		}
	}
}

bool VM::IsReg(string reg) {
	return 
	(reg.compare("r0") == 0) || 
	(reg.compare("r1") == 0) ||
	(reg.compare("r2") == 0) || 
	(reg.compare("r3") == 0) ||
	(reg.compare("r4") == 0) || 
	(reg.compare("r5") == 0) || 
	(reg.compare("r6") == 0);
}

int VM::GetRegIndex(string reg) {
	if(reg.compare("r0") == 0) return 0;
	if(reg.compare("r1") == 0) return 1;
	if(reg.compare("r2") == 0) return 2;
	if(reg.compare("r3") == 0) return 3;
	if(reg.compare("r4") == 0) return 4; 
	if(reg.compare("r5") == 0) return 5;
	if(reg.compare("r6") == 0) return 6;
	throw string(reg + " not found");
}

bool VM::IsAddress(string addr) {
	return (addr.rfind("@", 0) == 0);
}

int VM::GetAddressIndex(string reg) {
	reg.erase(0, 1);
	return stoi(reg);
}

VM::~VM() {
	
}