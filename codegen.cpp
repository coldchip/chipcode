#include "codegen.h"

CodeGen::CodeGen() {
	this->bytecode = new ByteCode;
	this->fp = fopen("test/out.S", "wb");
}

/*
void CodeGen::GenerateLoad(ASTIdentifier *e) {

}

*/

void CodeGen::GenerateStore(ASTIdentifier *e) {
	// Generates instructions to store reg r0 to identifier
	cout << "GenStore" << endl;
	this->bytecode->Emit(OP_MOV, "@" + to_string(e->offset), "r0");
}


void CodeGen::visit(ASTProgram *e) {
	cout << "ASTProgram" << endl;

	vector<ASTNode*> functions = e->functions;
	for(ASTNode *each : functions) {
		each->accept(this);
	}

	delete e;
}

void CodeGen::visit(ASTParams *e) {
	cout << "ASTParams" << endl;

	vector<ASTNode*> params = e->params;
	for(ASTNode *each : params) {
		each->accept(this);
	}

	delete e;
}

void CodeGen::visit(ASTArgs *e) {
	cout << "ASTArgs" << endl;

	vector<ASTNode*> args = e->args;
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

	ASTNode *body = e->body;

	if(body) {
		string prev_label = this->bytecode->GetCurrentWorkingProcedure();
		string label = this->RandomLabel(6);
		this->bytecode->Emit(OP_CALL, label, "");
		this->bytecode->SetCurrentWorkingProcedure(label);
		body->accept(this);

		this->bytecode->Emit(OP_PUSH, "100000", "");
		this->bytecode->Emit(OP_POP, "r3", "");
		this->bytecode->Emit(OP_CMP, "r0", "r3");

		this->bytecode->Emit(OP_JLZ, label, "");
		this->bytecode->SetCurrentWorkingProcedure(prev_label);
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
	//this->bytecode->Emit(OP_POP, "r0", "");
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
		this->bytecode->Emit(OP_POP, "r0", "");
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
	this->bytecode->Emit(OP_POP, "r0", "");
	this->bytecode->Emit(OP_POP, "r1", "");
	switch(e->oper) {
		case OPER_ADD: {
			this->bytecode->Emit(OP_ADD, "r0", "r1");
		}
		break;
		case OPER_SUB: {
			this->bytecode->Emit(OP_SUB, "r0", "r1");
		}
		break;
		case OPER_MUL: {
			this->bytecode->Emit(OP_MUL, "r0", "r1");
		}
		break;
		case OPER_DIV: {
			this->bytecode->Emit(OP_DIV, "r0", "r1");
		}
		break;
		case OPER_ASSIGN: {
			
		}
		break;
	}
	this->bytecode->Emit(OP_PUSH, "r0", "");
	delete e;
}

void CodeGen::visit(ASTLiteral *e) {
	cout << "ASTLiteral " << to_string(e->value) << endl;
	this->bytecode->Emit(OP_PUSH, to_string(e->value).c_str(), "");
	delete e;
}

void CodeGen::visit(ASTIdentifier *e) {
	cout << "ASTIdentifier " << e->value << endl;
	this->bytecode->Emit(OP_PUSH, "@" + to_string(e->offset), "");
	delete e;
}

void CodeGen::visit(ASTCall *e) {
	cout << "ASTCall" << endl;

	ASTNode* args = e->args;
	args->accept(this);
	
	this->bytecode->Emit(OP_CALL, e->name.c_str(), "");
	fprintf(this->fp, "call %s\n", e->name.c_str());
	delete e;
}

string CodeGen::RandomLabel(const int len) {
    string tmp_s;
    static const char alphanum[] =
        "0123456789abcdefghijklmnopqrstuvwxyz";
    srand((unsigned)time(NULL));
    tmp_s.reserve(len);
    for (int i = 0; i < len; ++i) {
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
    }
    return "sub_" + tmp_s;
}

CodeGen::~CodeGen() {
	this->bytecode->Dump();
	VM vm(this->bytecode->Build());
	vm.Run("main");

	delete this->bytecode;
	fclose(this->fp);
}