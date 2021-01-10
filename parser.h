#ifndef PARSER_H
#define PARSER_H

#include "tokenizer.h"
#include "scope.h"

using namespace std;

class ASTVisitor {
	public:
		virtual void visit(class ASTFunction *elem) = 0;
		virtual void visit(class ASTBlock *elem) = 0;
		virtual void visit(class ASTStmt *elem) = 0;
		virtual void visit(class ASTDecl *elem) = 0;
		virtual void visit(class ASTExpr *elem) = 0;
		virtual void visit(class ASTBinaryExpr *elem) = 0;
		virtual void visit(class ASTLiteral *elem) = 0;
		virtual void visit(class ASTIdentifier *elem) = 0;
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
		string name;
		vector<ASTNode*> stmt;
};

class ASTBlock : public ASTNode {
	public:
		void accept(ASTVisitor *visitor) override {
			visitor->visit(this);
		};
		vector<ASTNode*> stmt;
};

class ASTStmt : public ASTNode {
	public:
		void accept(ASTVisitor *visitor) override {
			visitor->visit(this);
		};
};

class ASTDecl : public ASTNode {
	public:
		void accept(ASTVisitor *visitor) override {
			visitor->visit(this);
		};
		string name;
		ASTNode *body = NULL;
};

class ASTExpr : public ASTNode {
	public:
		void accept(ASTVisitor *visitor) override {
			visitor->visit(this);
		};
};

class ASTBinaryExpr : public ASTNode {
	public:
		void accept(ASTVisitor *visitor) override {
			visitor->visit(this);
		};
		ASTNode *left = NULL;
		ASTNode	*right = NULL;
};

class ASTLiteral : public ASTNode {
	public:
		void accept(ASTVisitor *visitor) override {
			visitor->visit(this);
		};
		int value;
};

class ASTIdentifier : public ASTNode {
	public:
		void accept(ASTVisitor *visitor) override {
			visitor->visit(this);
		};
		string value;
};

class Parser {
	public:
		Parser(vector<Token> tokens);
		ASTNode *start();
		~Parser();
	private:
		vector<Token> tokens;
		Token token;
		unsigned index = 0;

		Scope *scope;

		void ConsumeToken();
		bool ConsumeToken(string type);
		bool ConsumeToken(TokenType type);
		void ExpectToken(string type);
		void ExpectToken(TokenType type);
		bool PeekToken(string d);
		bool PeekToken(TokenType type);

		ASTNode *ParseStmt();
		ASTNode *ParseFunction();
		ASTNode *ParseDecl();

		ASTNode *ParseExpr();
		ASTNode *ParseAssign();
		ASTNode *ParsePlus();
		ASTNode *ParseMinus();
		ASTNode *ParseMultiply();
		ASTNode *ParseDivide();
		ASTNode *ParseEquality();
		ASTNode *ParsePrimary();
};

#endif