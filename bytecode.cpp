#include "bytecode.h"

ByteCode::ByteCode() {

}

void ByteCode::SetCurrentWorkingProcedure(string name) {
	this->currentProcedure = name;
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

void ByteCode::Dump() {
	cout << "-----BEGIN DUMP-----" << endl;
	for(Procedure &proc : this->program) {
		cout << proc.name << ":" << endl;
		for(Instruction &ins : proc.instructions) {
			cout << "\t" << to_string(ins.op) << " " << ins.left << " " << ins.right << endl;
		}
	}
	cout << "-----END DUMP-----" << endl;
}

vector<Procedure> ByteCode::Build() {
	return this->program;
}

ByteCode::~ByteCode() {
	
}