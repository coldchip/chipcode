#ifndef PARSER_H
#define PARSER_H

#include "tokenizer.h"
#include "scope.h"

using namespace std;

typedef enum {
	OPER_ADD,
	OPER_SUB,
	OPER_MUL,
	OPER_DIV,
	OPER_ASSIGN
} Operator;

class ASTVisitor {
	public:
		virtual void visit(class ASTProgram *elem) = 0;
		virtual void visit(class ASTParams *elem) = 0;
		virtual void visit(class ASTArgs *elem) = 0;
		virtual void visit(class ASTFunction *elem) = 0;
		virtual void visit(class ASTBlock *elem) = 0;
		virtual void visit(class ASTStmt *elem) = 0;
		virtual void visit(class ASTDecl *elem) = 0;
		virtual void visit(class ASTExpr *elem) = 0;
		virtual void visit(class ASTAssign *elem) = 0;
		virtual void visit(class ASTBinaryExpr *elem) = 0;
		virtual void visit(class ASTLiteral *elem) = 0;
		virtual void visit(class ASTIdentifier *elem) = 0;
		virtual void visit(class ASTCall *elem) = 0;
};

class ASTNode {
	public:
		virtual ~ASTNode() {}
		virtual void accept(ASTVisitor *visitor) = 0;
};

class ASTProgram : public ASTNode {
	public:
		void accept(ASTVisitor *visitor) override {
			visitor->visit(this);
		};
		vector<ASTNode*> functions;
};

class ASTParams : public ASTNode {
	public:
		void accept(ASTVisitor *visitor) override {
			visitor->visit(this);
		};
		vector<ASTNode*> params;
};

class ASTArgs : public ASTNode {
	public:
		void accept(ASTVisitor *visitor) override {
			visitor->visit(this);
		};
		vector<ASTNode*> args;
};

class ASTFunction : public ASTNode {
	public:
		void accept(ASTVisitor *visitor) override {
			visitor->visit(this);
		};
		string name;
		ASTNode *params;
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
		int offset = 0;
		ASTNode *body = NULL;
};

class ASTExpr : public ASTNode {
	public:
		void accept(ASTVisitor *visitor) override {
			visitor->visit(this);
		};
};

class ASTAssign : public ASTNode {
	public:
		void accept(ASTVisitor *visitor) override {
			visitor->visit(this);
		};
		ASTNode *left = NULL;
		ASTNode	*right = NULL;
};

class ASTBinaryExpr : public ASTNode {
	public:
		void accept(ASTVisitor *visitor) override {
			visitor->visit(this);
		};
		Operator oper;
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
		int offset = 0;
};

class ASTCall : public ASTNode {
	public:
		void accept(ASTVisitor *visitor) override {
			visitor->visit(this);
		};
		ASTNode *args;
		string name;
};

class Parser {
	public:
		Parser(vector<Token> tokens);
		ASTNode *start();
		~Parser();
	private:
		vector<Token> tokens;
		Token token;
		int index = -1; // Always starts at -1 because first token is always uninitialized

		Scope *scope;

		void UnconsumeToken();
		void ConsumeToken();
		bool ConsumeToken(string type);
		bool ConsumeToken(TokenType type);
		void ExpectToken(string type);
		void ExpectToken(TokenType type);
		bool PeekToken(string d);
		bool PeekToken(TokenType type);
		bool IsCall();
		bool IsTypeName();

		ASTNode *ParseBaseType();
		ASTNode *ParseCall();
		ASTNode *ParseStmt();
		ASTNode *ParseFunction();
		ASTNode *ParseDecl();

		ASTNode *ParseParameter();
		ASTNode *ParseParameters();
		ASTNode *ParseArgument();
		ASTNode *ParseArguments();

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