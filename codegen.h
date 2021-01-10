#ifndef CODEGEN_H
#define CODEGEN_H

#include "parser.h"

class CodeGen : public ASTVisitor {
	public:
		CodeGen();
		~CodeGen();
	private:
		FILE *fp = NULL;

		void visit(ASTFunction *e) override;
		void visit(ASTBlock *e) override;
		void visit(ASTStmt *e) override;
		void visit(ASTDecl *e) override;
		void visit(ASTExpr *e) override;
		void visit(ASTBinaryExpr *e) override;
		void visit(ASTLiteral *e) override;
		void visit(ASTIdentifier *e) override;
};

#endif