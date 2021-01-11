#include "codegen.h"

CodeGen::CodeGen() {
	this->bytecode = new ByteCode;
	this->fp = fopen("test/out.S", "wb");
}

CodeGen::GenerateLoad(ASTIdentifier *e) {

}

CodeGen::GenerateStore(ASTIdentifier *e) {

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
	}
	if(left) {
		left->accept(this);
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
	fprintf(this->fp, "push %s\n", to_string(e->value).c_str());
	delete e;
}

void CodeGen::visit(ASTIdentifier *e) {
	cout << "ASTIdentifier " << e->value << endl;
	this->bytecode->Emit(OP_PUSH, "@" + to_string(e->offset), "");
	fprintf(this->fp, "push %s\n", e->value.c_str());
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

CodeGen::~CodeGen() {
	this->bytecode->Dump();
	VM vm(this->bytecode->Build());
	vm.Run("main");

	delete this->bytecode;
	fclose(this->fp);
}