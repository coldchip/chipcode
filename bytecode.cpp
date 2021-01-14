#include "bytecode.h"

ByteCode::ByteCode() {

}

void ByteCode::SetCurrentWorkingProcedure(string name) {
	this->currentProcedure = name;
}

string ByteCode::GetCurrentWorkingProcedure() {
	return this->currentProcedure;
}

Procedure &ByteCode::GetProcedure(string name) {
	for(Procedure &proc : this->program) {
		if(proc.name.compare(name) == 0) {
			return proc;
		}
	}
	Procedure newProc;
	newProc.name = name;
	this->program.push_back(newProc);
	return this->GetProcedure(name);
}

void ByteCode::Emit(OPCode op, string left, string right) {
	Instruction ins;
	ins.op = op;
	ins.left = left;
	ins.right = right;

	Procedure &proc = this->GetProcedure(this->currentProcedure);
	proc.instructions.push_back(ins);
}

string ByteCode::GetInstructionAsString(OPCode op) {
	switch(op) {
		case OP_POP:
			return "pop";
		break;
		case OP_PUSH:
			return "push";
		break;
		case OP_ADD:
			return "add";
		break;
		case OP_SUB:
			return "sub";
		break;
		case OP_MUL:
			return "mul";
		break;
		case OP_DIV:
			return "div";
		break;
		case OP_CALL:
			return "call";
		break;
		case OP_MOV:
			return "mov";
		break;
		case OP_CMP:
			return "cmp";
		break;
		case OP_JMP:
			return "jmp";
		break;
		case OP_JE:
			return "je";
		break;
		case OP_JNE:
			return "jne";
		break;
		case OP_JLZ:
			return "jlz";
		break;
		case OP_JGZ:
			return "jgz";
		break;
		case OP_SETGT:
			return "setgt";
		break;
		case OP_SETLT:
			return "setlt";
		break;
		default:
			return "nop";
		break;
	}
}

void ByteCode::Dump() {
	cout << "-----BEGIN DUMP-----" << endl;
	for(Procedure &proc : this->program) {
		cout << proc.name << ":" << endl;
		for(Instruction &ins : proc.instructions) {
			string op = this->GetInstructionAsString(ins.op);
			cout << "\t" << op << " " << ins.left << " " << ins.right << endl;
		}
	}
	cout << "-----END DUMP-----" << endl;
}

vector<Procedure> ByteCode::Build() {
	return this->program;
}

ByteCode::~ByteCode() {
	
}