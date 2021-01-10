#include "codegen.h"

CodeGen::CodeGen() {
	this->bytecode = new ByteCode;
	this->fp = fopen("test/out.S", "wb");
}

void CodeGen::visit(ASTProgram *e) {
	cout << "ASTProgram" << endl;

	vector<ASTNode*> functions = e->functions;
	for(ASTNode *each : functions) {
		each->accept(this);
	}

	delete e;
}

void CodeGen::visit(ASTFunction *e) {
	cout << "ASTFunction" << endl;

	fprintf(this->fp, "proc %s\n", e->name.c_str());

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
	body->accept(this);
	fprintf(this->fp, "pop r0\n");
	fprintf(this->fp, "setvar %s r0\n", e->name.c_str());
	delete e;
}

void CodeGen::visit(ASTExpr *e) {
	cout << "ASTExpr" << endl;
	delete e;
}

void CodeGen::visit(ASTBinaryExpr *e) {
	ASTNode *left = e->left;
	ASTNode *right = e->right;
	right->accept(this);
	left->accept(this);
	cout << "ASTBinaryExpr" << endl;
	fprintf(this->fp, "pop r0\n");
	fprintf(this->fp, "pop r1\n");
	fprintf(this->fp, "add r0 r1\n");
	fprintf(this->fp, "push r0\n");
	delete e;
}

void CodeGen::visit(ASTLiteral *e) {
	cout << "ASTLiteral " << to_string(e->value) << endl;
	fprintf(this->fp, "push %s\n", to_string(e->value).c_str());
	delete e;
}

void CodeGen::visit(ASTIdentifier *e) {
	cout << "ASTIdentifier " << e->value << endl;
	fprintf(this->fp, "push %s\n", e->value.c_str());
	delete e;
}

void CodeGen::visit(ASTCall *e) {
	cout << "ASTCall" << endl;
	fprintf(this->fp, "call %s\n", e->name.c_str());
	delete e;
}

CodeGen::~CodeGen() {
	delete this->bytecode;
	fclose(this->fp);
}