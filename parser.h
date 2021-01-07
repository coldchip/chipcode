#ifndef PARSER_H
#define PARSER_H

#include "tokenizer.h"

using namespace std;

class ASTVisitor {
	public:
		virtual void visit(class ASTFunction *elem) = 0;
		virtual void visit(class ASTStmt *elem) = 0;
		virtual void visit(class ASTExpr *elem) = 0;
};

class ASTNode {
	public:
		virtual ~ASTNode() {}
		virtual void accept(ASTVisitor *visitor) = 0;
};

class ASTFunction : public ASTNode {
	public:
		void accept(ASTVisitor *visitor) override {
			visitor->visit(this);
		};
		vector<ASTStmt*> stmt;
};

class ASTStmt : public ASTNode {
	public:
		void accept(ASTVisitor *visitor) override {
			visitor->visit(this);
		};
};

class ASTExpr : public ASTStmt {
	public:
		void accept(ASTVisitor *visitor) override {
			visitor->visit(this);
		};
};







class Parser {
	public:
		Parser(vector<Token> tokens);
		ASTNode *start();
		~Parser();
	private:
		vector<Token> tokens;
		Token token;
		vector<Token>::iterator il;

		void ConsumeToken();
		bool ConsumeToken(string type);
		bool ConsumeToken(TokenType type);
		void ExpectToken(string type);
		void ExpectToken(TokenType type);
		bool PeekToken(string d);
		bool PeekToken(TokenType type);

		ASTNode *ParseStmt();
		ASTNode *ParseFunction();

		void ParseExpr();
		void ParseAssign();
		void ParsePlus();
		void ParseMinus();
		void ParseMultiply();
		void ParseDivide();
		void ParseEquality();
		void ParsePrimary();
};

#endif