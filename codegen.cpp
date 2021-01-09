#include "codegen.h"

CodeGen::CodeGen() {
	this->fp = fopen("test/out.S", "wb");
}

void CodeGen::visit(ASTFunction *e) {
	cout << "ASTFunction" << endl;

	fprintf(this->fp, "proc %s\n", e->name.c_str());

	vector<ASTStmt*> stmt = e->stmt;
	for(ASTStmt *each : stmt) {
		each->accept(this);
	}

	delete e;
}

void CodeGen::visit(ASTStmt *e) {
	cout << "ASTStmt" << endl;
}

void CodeGen::visit(ASTDecl *e) {
	cout << "ASTDecl" << endl;
	ASTNode *body = e->body;
	body->accept(this);
}

void CodeGen::visit(ASTExpr *e) {
	cout << "ASTExpr" << endl;
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
	fprintf(this->fp, "push r0\n\n");
}

void CodeGen::visit(ASTLiteral *e) {
	cout << "ASTLiteral " << to_string(e->value) << endl;
	fprintf(this->fp, "push %s\n", to_string(e->value).c_str());
}

void CodeGen::visit(ASTIdentifier *e) {
	cout << "ASTIdentifier " << e->value << endl;
	fprintf(this->fp, "push %s\n", e->value.c_str());
}

CodeGen::~CodeGen() {
	fclose(this->fp);
}