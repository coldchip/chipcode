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

	throw string("unable to find procedure: " + name);
}

void VM::Run(string name) {
	Procedure &proc = this->GetProcedure(name);
	char stack[65535];
	memset(stack, 0 , sizeof(stack));

	int reg[32];
	memset(reg, 0 , sizeof(reg));

	int fp = 0;
	int sp = 0;
	this->ExecProcedure(proc, (char*)&stack, (int*)&reg, fp, sp);
}

void VM::ExecProcedure(Procedure &proc, char *stack, int *reg, int fp, int sp) {
	bool cmp_flag = false;
	bool cmplt_flag = false;
	bool cmpgt_flag = false;

	sp += fp;

	jmp:

	for(Instruction &ins : proc.instructions) {
		OPCode op = ins.op;
		VType ltype = ins.ltype;
		string left = ins.left;
		VType rtype = ins.rtype;
		string right = ins.right;
		switch(op) {
			case OP_PUSH: {
				if(ltype == V_REG) {
					int i = stoi(left);
					*(int*)(stack + sp) = *(reg + i);
				} else if(ltype == V_ADDR) {
					int i = stoi(left);
					int *a = (int*)(stack + i);
					*(int*)(stack + sp) = *a;
				} else {
					*(int*)(stack + sp) = stoi(left);
				}
				sp += 4;
			}
			break;
			case OP_POP: {
				sp -= 4;
				if(ltype == V_REG) {
					int i = stoi(left);
					*(reg + i) = *(int*)(stack + sp);
				} else if(ltype == V_ADDR) {
					int i = stoi(left);
					int *a = (int*)(stack + i);
					*a = *(int*)(stack + sp);
				} else {
					throw string("pop to a literal isn't allowed");
				}
			}
			break;
			case OP_ADD: {
				if(ltype == V_REG && rtype == V_REG) {
					int a = stoi(left);
					int b = stoi(right);
					*(reg + a) += *(reg + b);
				} else {
					throw string("add only can be done to regs");
				}
			}
			break;
			case OP_SUB: {
				if(ltype == V_REG && rtype == V_REG) {
					int a = stoi(left);
					int b = stoi(right);
					*(reg + a) -= *(reg + b);
				} else {
					throw string("add only can be done to regs");
				}
			}
			break;
			case OP_MUL: {
				if(ltype == V_REG && rtype == V_REG) {
					int a = stoi(left);
					int b = stoi(right);
					*(reg + a) *= *(reg + b);
				} else {
					throw string("add only can be done to regs");
				}
			}
			break;
			case OP_DIV: {
				if(ltype == V_REG && rtype == V_REG) {
					int a = stoi(left);
					int b = stoi(right);
					*(reg + a) /= *(reg + b);
				} else {
					throw string("add only can be done to regs");
				}
			}
			break;
			case OP_MOV: {
				int a = 0;
				if(rtype == V_REG) {
					int i = stoi(right);
					a = *(reg + i);
				}
				if(rtype == V_ADDR) {
					int i = stoi(right);
					a = *(int*)(stack + i + fp);
				}
				if(ltype == V_REG) {
					int i = stoi(left);
					*(reg + i) = a;
				} 
				if(ltype == V_ADDR) {
					int i = stoi(left);
					*(int*)(stack + i + fp) = a;
				}
			}
			break;
			case OP_CALL: {
				if(ltype == V_LABEL) {
					if(left.compare("dbgregs") == 0) {
						printf("----- DUMP REGISTERS -----\n");
						printf("Frame PTR: %i\n", fp);
						printf("Stack PTR: %i\n", sp);
						printf("R0: %i\n", reg[0]);
						printf("R1: %i\n", reg[1]);
						printf("R2: %i\n", reg[2]);
						printf("R3: %i\n", reg[3]);
						printf("R4: %i\n", reg[4]);
						printf("R5: %i\n", reg[5]);
					} else if(left.compare("dbgstack") == 0) {
						printf("----- DUMP STACK -----\n");
						for(int i = 0; i < 256; i++) {
							if(i % 4 == 0) {
								printf("\n%i: ", i);
							}
							printf("%02x", *(stack + i) & 0xFF);
						}
						printf("\n");
					} else if(left.compare("halt") == 0) {
						printf("halt() called, halting\n");
						exit(0);
					} else {
						Procedure &sub = this->GetProcedure(left);
						this->ExecProcedure(sub, stack, reg, sp, 0);
					}
				}
			}
			break;
			case OP_CMP: {
				if(ltype == V_REG && rtype == V_REG) {
					int ia = stoi(left);
					int a = *(reg + ia);
					int ib = stoi(right);
					int b = *(reg + ib);

					cmp_flag = false;
					cmplt_flag = false;
					cmpgt_flag = false;
					if(a == b) {
						cmp_flag = true;
					} else if(a < b) {
						cmplt_flag = true;
					} else if(a > b) {
						cmpgt_flag = true;
					}
				}
			}
			break;
			case OP_JMP: {
				// unconditional jump
				if(ltype == V_LABEL) {
					proc = this->GetProcedure(left);
					goto jmp; // very dirty way to do this
				}
			}
			break;
			case OP_JE: {
				// jump if equals
				if(ltype == V_LABEL) {
					if(cmp_flag == true) {
						proc = this->GetProcedure(left);
						goto jmp; // very dirty way to do this
					}
				}
			}
			break;
			case OP_JNE: {
				// jump if not equals
				if(ltype == V_LABEL) {
					if(cmp_flag == false) {
						proc = this->GetProcedure(left);
						goto jmp; // very dirty way to do this
					}
				}
			}
			break;
			case OP_JLZ: {
				// jump if less than
				if(ltype == V_LABEL) {
					if(cmplt_flag == true) {
						proc = this->GetProcedure(left);
						goto jmp; // very dirty way to do this
					}
				}
			}
			break;
			case OP_JGZ: {
				// jump if greater than
				if(ltype == V_LABEL) {
					if(cmpgt_flag == true) {
						proc = this->GetProcedure(left);
						goto jmp; // very dirty way to do this
					}
				}
			}
			break;
			case OP_SETGT: {
				// set gt
				if(ltype == V_REG) {
					int i = stoi(left);
					if(cmpgt_flag == true) {
						*(reg + i) = 1;
					} else {
						*(reg + i) = 0;
					}
				} else {
					throw string("setlt expects a reg");
				}
			}
			break;
			case OP_SETLT: {
				// set lt
				if(ltype == V_REG) {
					int i = stoi(left);
					if(cmplt_flag == true) {
						*(reg + i) = 1;
					} else {
						*(reg + i) = 0;
					}
				} else {
					throw string("setlt expects a reg");
				}
			}
			break;
			case OP_SETSP: {
				// set sp
				if(ltype == V_REG) {
					int i = stoi(left);
					sp = *(reg + i);
				}
			}
			break;
			case OP_GETSP: {
				// get sp
				if(ltype == V_REG) {
					int i = stoi(left);
					*(reg + i) = sp;
				}
			}
			break;
			case OP_MOVDR: {
				// deref
				if(ltype == V_REG && rtype == V_REG) {
					int ib = stoi(right);
					int b  = *(reg + ib);
					int ia = stoi(left);
					*(reg + ia) = *(int*)(stack + b);
				}
			}
			break;
			case OP_NOP: {
				// nothing
			}
			break;
		}
	}
}

VM::~VM() {
	
}