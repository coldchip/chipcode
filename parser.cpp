#include "parser.h"

Parser::Parser(vector<Token>& tokens) {
	this->tokens = tokens;
	this->il = tokens.begin();
	this->token = *this->il;

	this->PushStack();
}

void Parser::ConsumeToken() {
	this->il++;
	this->token = *this->il;
}

bool Parser::ConsumeToken(string d) {
	if(this->PeekToken(d)) {
		this->ConsumeToken();
		return true;
	}
	return false;
}

bool Parser::ConsumeToken(TokenType type) {
	if(this->PeekToken(type)) {
		this->ConsumeToken();
		return true;
	}
	return false;
}

void Parser::ExpectToken(string d) {
	if(!this->ConsumeToken(d)) {
		throw string("Unable to parse, expecting ") + d + string(" at line ") + to_string(this->token.line);
	}
}

void Parser::ExpectToken(TokenType type) {
	if(!this->ConsumeToken(type)) {
		throw string("Unable to parse, expecting type ") + to_string(type) + string(" at line ") + to_string(this->token.line);
	}
}

bool Parser::PeekToken(string d) {
	return (this->token.value.compare(d) == 0);
}

bool Parser::PeekToken(TokenType type) {
	return (this->token.type == type);
}

ASTNode *Parser::ParseStmt() {
	ASTStmt *node = new ASTStmt;
	if(this->PeekToken("while")) {
		this->ExpectToken("while");
		this->ExpectToken("(");
		this->ParseExpr();
		this->ExpectToken(")");
		this->ParseStmt();
	} else if(this->PeekToken("{")) {
		this->PushStack();

		this->ExpectToken("{");
		while(!this->PeekToken("}")) {
			this->ParseStmt();
		}
		this->ExpectToken("}");

		this->PopStack();
	} else if(this->PeekToken("var")) {
		ASTNode *decl = this->ParseDecl();
		this->ExpectToken(";");
		return decl;
	} else {
		ASTNode *expr = this->ParseExpr();
		this->ExpectToken(";");
		return expr;
	}
	return node;
}

ASTNode *Parser::ParseFunction() {
	ASTFunction *node = new ASTFunction;

	this->PushStack();

	this->ExpectToken("function");
	node->name = this->token.value;
	this->ExpectToken(TT_KEYWORD);
	this->ExpectToken("(");
	this->ExpectToken(")");
	this->ExpectToken("{");
	// Parse Body
	while(!this->PeekToken("}")) {
		node->stmt.push_back((ASTStmt*)this->ParseStmt());
	}
	this->ExpectToken("}");

	this->PopStack();
	return node;
}

ASTNode *Parser::ParseDecl() {
	ASTDecl *node = new ASTDecl;
	this->ExpectToken("var");
	if(this->HasVar(this->token.value)) {
		throw string("variable '" + this->token.value + "' already defined");
	}
	this->AddVar(this->token.value);
	this->ExpectToken(TT_KEYWORD);
	if(this->ConsumeToken("=")) {
		node->body = this->ParseExpr();
	}
	return node;
}

ASTNode *Parser::start() {
	return this->ParseFunction();
}

Parser::~Parser() {

}