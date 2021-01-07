#ifndef CODEGEN_H
#define CODEGEN_H

#include "parser.h"

class CodeGen : public ASTVisitor {
	public:
		void visit(ASTFunction *e) override;
		void visit(ASTStmt *e) override;
		void visit(ASTExpr *e) override;
};

#endif