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

void ByteCode::Emit(OPCode op, VType ltype, string left, VType rtype, string right) {
	Instruction ins;
	ins.op = op;
	ins.ltype = ltype;
	ins.left = left;
	ins.rtype = rtype;
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
		case OP_SETSP:
			return "setsp";
		break;
		case OP_GETSP:
			return "getsp";
		break;
		case OP_MOVDR:
			return "movdr";
		break;
		default:
			return "nop";
		break;
	}
}

string ByteCode::GetVTypeAsString(VType type) {
	switch(type) {
		case V_REG:
			return "r";
		break;
		case V_ADDR:
			return "@";
		break;
		case V_VALUE:
			return "#";
		break;
		case V_LABEL:
			return "";
		break;
		case V_NONE:
			return "?";
		break;
		default:
			return "";
		break;
	}
}

void ByteCode::Dump() {
	FILE *fp = fopen("test/out.S", "wb");
	for(Procedure &proc : this->program) {
		printf("%s\n", proc.name.c_str());
		fprintf(fp, "%s\n", proc.name.c_str());

		for(Instruction &ins : proc.instructions) {
			string op = this->GetInstructionAsString(ins.op);
			string ltype = this->GetVTypeAsString(ins.ltype);
			string rtype = this->GetVTypeAsString(ins.rtype);
			
			if(ins.rtype == V_NONE) {
				printf("\t%s %s%s\n", op.c_str(), ltype.c_str(), ins.left.c_str());
				fprintf(fp, "\t%s %s%s\n", op.c_str(), ltype.c_str(), ins.left.c_str());
			} else {
				printf("\t%s %s%s %s%s\n", op.c_str(), ltype.c_str(), ins.left.c_str(), rtype.c_str(), ins.right.c_str());
				fprintf(fp, "\t%s %s%s %s%s\n", op.c_str(), ltype.c_str(), ins.left.c_str(), rtype.c_str(), ins.right.c_str());
			}
		}
	}
	fclose(fp);
}

vector<Procedure> ByteCode::Build() {
	return this->program;
}

ByteCode::~ByteCode() {
	
}