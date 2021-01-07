#include "codegen.h"

void CodeGen::visit(ASTFunction *e) {
	cout << "ASTFunction" << endl;
	vector<ASTStmt*> stmt = e->stmt;
	for(ASTStmt *each : stmt) {
		each->accept(this);
	}

	delete e;
}

void CodeGen::visit(ASTStmt *e) {
	cout << "ASTStmt" << endl;
}

void CodeGen::visit(ASTExpr *e) {
	cout << "ASTExpr" << endl;
}