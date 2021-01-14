#ifndef CODEGEN_H
#define CODEGEN_H

#include "parser.h"
#include "bytecode.h"
#include "vm.h"

using namespace std;

class CodeGen : public ASTVisitor {
	public:
		CodeGen();
		~CodeGen();
	private:
		ByteCode *bytecode;

		int labelcounter = 0;

		void GenerateStore(ASTIdentifier *e);
		void GeneratePushStack();
		void GeneratePopStack();

		void visit(ASTProgram *e) override;
		void visit(ASTParams *e) override;
		void visit(ASTArgs *e) override;
		void visit(ASTFunction *e) override;
		void visit(ASTWhile *e) override;
		void visit(ASTIf *e) override;
		void visit(ASTBlock *e) override;
		void visit(ASTStmt *e) override;
		void visit(ASTDecl *e) override;
		void visit(ASTExpr *e) override;
		void visit(ASTAssign *e) override;
		void visit(ASTBinaryExpr *e) override;
		void visit(ASTLiteral *e) override;
		void visit(ASTIdentifier *e) override;
		void visit(ASTCall *e) override;

		string RandomLabel();
};

#endif