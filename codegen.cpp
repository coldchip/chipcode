#include "codegen.h"

CodeGen::CodeGen() {
	this->bytecode = new ByteCode;
}

/*
void CodeGen::GenerateLoad(ASTIdentifier *e) {

}

*/

void CodeGen::GenerateStore(ASTIdentifier *e) {
	// Generates instructions to store reg r0 to identifier
	cout << "GenStore" << endl;
	this->bytecode->Emit(OP_MOV, V_ADDR, to_string(e->offset), V_REG, "0");
}

void CodeGen::GeneratePushStack() {
	// Generates instructions to save the current stack ptr
	// this->bytecode->Emit(OP_NOP, "", "");
}

void CodeGen::GeneratePopStack() {
	// Generates instructions to rewind the previous stack ptr
}


void CodeGen::visit(ASTProgram *e) {
	cout << "ASTProgram" << endl;

	vector<ASTNode*> functions = e->functions;
	for(ASTNode *each : functions) {
		each->accept(this);
	}

	this->bytecode->Dump();
	VM vm(this->bytecode->Build());
	vm.Run("main");

	delete e;
}

void CodeGen::visit(ASTParams *e) {
	cout << "ASTParams" << endl;

	vector<ASTNode*> params = e->params;
	for(ASTNode *each : params) {
		//each->accept(this);
		this->bytecode->Emit(OP_MOVDR, V_REG, "0", V_REG, "5"); // deref pointer
		this->GenerateStore((ASTIdentifier*)each);
	}

	delete e;
}

void CodeGen::visit(ASTArgs *e) {
	cout << "ASTArgs" << endl;

	vector<ASTNode*> args = e->args;
	this->bytecode->Emit(OP_GETSP, V_REG, "5", V_NONE, "");
	for(ASTNode *each : args) {
		each->accept(this);
	}

	delete e;
}

void CodeGen::visit(ASTFunction *e) {
	cout << "ASTFunction" << endl;

	this->bytecode->SetCurrentWorkingProcedure(e->name);

	ASTNode* params = e->params;
	params->accept(this);

	vector<ASTNode*> stmt = e->stmt;
	for(ASTNode *each : stmt) {
		each->accept(this);
	}

	delete e;
}

void CodeGen::visit(ASTWhile *e) {
	cout << "ASTWhile" << endl;
	ASTNode *condition = e->condition;
	ASTNode *body = e->body;

	if(condition && body) {
		string label = this->RandomLabel();
		string continue_label = this->RandomLabel();
		this->bytecode->Emit(OP_JMP, V_LABEL, label, V_NONE, "");
		this->bytecode->SetCurrentWorkingProcedure(label);
		condition->accept(this);
		this->bytecode->Emit(OP_PUSH, V_VALUE, "1", V_NONE, "");
		this->bytecode->Emit(OP_POP, V_REG, "0", V_NONE, "");
		this->bytecode->Emit(OP_POP, V_REG, "3", V_NONE, "");
		this->bytecode->Emit(OP_CMP, V_REG, "0", V_REG, "3");
		this->bytecode->Emit(OP_JNE, V_LABEL, continue_label, V_NONE, "");

		body->accept(this);

		this->bytecode->Emit(OP_JMP, V_LABEL, label, V_NONE, "");
		this->bytecode->SetCurrentWorkingProcedure(continue_label);
	}

	delete e;
}

void CodeGen::visit(ASTIf *e) {
	cout << "ASTIf" << endl;
	ASTNode *condition = e->condition;
	ASTNode *body = e->body;
	ASTNode *alternative = e->alternative;

	if(condition && body) {
		condition->accept(this);

		string body_label = this->RandomLabel();
		string else_label = this->RandomLabel();
		string exit_label = this->RandomLabel();

		this->bytecode->Emit(OP_PUSH, V_VALUE, "1", V_NONE, "");
		this->bytecode->Emit(OP_POP, V_REG, "0", V_NONE, "");
		this->bytecode->Emit(OP_POP, V_REG, "3", V_NONE, "");
		this->bytecode->Emit(OP_CMP, V_REG, "0", V_REG, "3");
		this->bytecode->Emit(OP_JE, V_LABEL, body_label, V_NONE, "");
		this->bytecode->Emit(OP_JMP, V_LABEL, else_label, V_NONE, "");
		this->bytecode->SetCurrentWorkingProcedure(body_label);
		body->accept(this);
		this->bytecode->Emit(OP_JMP, V_LABEL, exit_label, V_NONE, "");
		this->bytecode->SetCurrentWorkingProcedure(else_label);

		if(alternative) {
			alternative->accept(this);
		}
		this->bytecode->Emit(OP_JMP, V_LABEL, exit_label, V_NONE, "");
		this->bytecode->SetCurrentWorkingProcedure(exit_label);
	}

	delete e;
}

void CodeGen::visit(ASTBlock *e) {
	cout << "ASTBlock" << endl;

	vector<ASTNode*> stmt = e->stmt;
	for(ASTNode *each : stmt) {
		each->accept(this);
	}

	delete e;
}

void CodeGen::visit(ASTStmt *e) {
	cout << "ASTStmt" << endl;
	delete e;
}

void CodeGen::visit(ASTDecl *e) {
	cout << "ASTDecl" << endl;
	ASTNode *body = e->body;
	if(body) {
		body->accept(this);
	}
	//this->bytecode->Emit(OP_POP, "0", "");
	delete e;
}

void CodeGen::visit(ASTExpr *e) {
	cout << "ASTExpr" << endl;
	delete e;
}

void CodeGen::visit(ASTAssign *e) {
	cout << "ASTAssign" << endl;
	ASTNode *left = e->left;
	ASTNode *right = e->right;
	if(right) {
		right->accept(this);
		this->bytecode->Emit(OP_POP, V_REG, "0", V_NONE, "");
	}
	if(left) {
		// left->accept(this);
		this->GenerateStore((ASTIdentifier*)left);
	}
}

void CodeGen::visit(ASTBinaryExpr *e) {
	ASTNode *left = e->left;
	ASTNode *right = e->right;
	if(right) {
		right->accept(this);
	}
	if(left) {
		left->accept(this);
	}
	cout << "ASTBinaryExpr" << endl;
	this->bytecode->Emit(OP_POP, V_REG, "0", V_NONE, "");
	this->bytecode->Emit(OP_POP, V_REG, "1", V_NONE, "");
	switch(e->oper) {
		case OPER_ADD: {
			this->bytecode->Emit(OP_ADD, V_REG, "0", V_REG, "1");
		}
		break;
		case OPER_SUB: {
			this->bytecode->Emit(OP_SUB, V_REG, "0", V_REG, "1");
		}
		break;
		case OPER_MUL: {
			this->bytecode->Emit(OP_MUL, V_REG, "0", V_REG, "1");
		}
		break;
		case OPER_DIV: {
			this->bytecode->Emit(OP_DIV, V_REG, "0", V_REG, "1");
		}
		break;
		case OPER_GT: {
			this->bytecode->Emit(OP_CMP, V_REG, "0", V_REG, "1");
			this->bytecode->Emit(OP_SETGT, V_REG, "0", V_NONE, "");
		}
		break;
		case OPER_LT: {
			this->bytecode->Emit(OP_CMP, V_REG, "0", V_REG, "1");
			this->bytecode->Emit(OP_SETLT, V_REG, "0", V_NONE, "");
		}
		break;
		case OPER_ASSIGN: {
			
		}
		break;
	}
	this->bytecode->Emit(OP_PUSH, V_REG, "0", V_NONE, "");
	delete e;
}

void CodeGen::visit(ASTLiteral *e) {
	cout << "ASTLiteral " << to_string(e->value) << endl;
	this->bytecode->Emit(OP_PUSH, V_VALUE, to_string(e->value).c_str(), V_NONE, "");
	delete e;
}

void CodeGen::visit(ASTIdentifier *e) {
	cout << "ASTIdentifier " << e->value << endl;
	this->bytecode->Emit(OP_PUSH, V_ADDR, to_string(e->offset), V_NONE, "");
	delete e;
}

void CodeGen::visit(ASTCall *e) {
	cout << "ASTCall" << endl;

	ASTNode* args = e->args;
	args->accept(this);
	
	this->bytecode->Emit(OP_CALL, V_LABEL, e->name, V_NONE, "");
	delete e;
}

string CodeGen::RandomLabel() {
    return ".L" + to_string(this->labelcounter++);
}

CodeGen::~CodeGen() {
	delete this->bytecode;
}