#include "parser.h"

Parser::Parser(vector<Token> tokens) {
	this->scope = new Scope;
	this->tokens = tokens;
	this->ConsumeToken();
	this->scope->PushScope(); // Push main frame
}

void Parser::UnconsumeToken() {
	try {
		this->token = this->tokens.at(--this->index);
	} catch(const std::out_of_range& e) {
		throw string("unexpected end-of-file reached in parser");
	}
}

void Parser::ConsumeToken() {
	try {
		this->token = this->tokens.at(++this->index);
	} catch(const std::out_of_range& e) {
		throw string("unexpected end-of-file reached in parser");
	}
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
		if(this->ConsumeToken(TT_EOF)) {
			throw string("EOF reached, expecting ") + d + string(" at line ") + to_string(this->token.line);
		} else {
			throw string("Unable to parse, expecting ") + d + string(" at line ") + to_string(this->token.line);
		}
	}
}

void Parser::ExpectToken(TokenType type) {
	if(!this->ConsumeToken(type)) {
		if(this->ConsumeToken(TT_EOF)) {
			throw string("EOF reached, expecting type ") + to_string(type) + string(" at line ") + to_string(this->token.line);
		} else {
			throw string("Unable to parse, expecting type ") + to_string(type) + string(" at line ") + to_string(this->token.line);
		}
	}
}

bool Parser::PeekToken(string d) {
	return (this->token.value.compare(d) == 0) && !(this->index < 0);
}

bool Parser::PeekToken(TokenType type) {
	return (this->token.type == type) && !(this->index < 0);
}

bool Parser::IsCall() {
	if(this->ConsumeToken(TT_KEYWORD)) {
		if(this->ConsumeToken("(")) {
			this->UnconsumeToken();
			this->UnconsumeToken();
			return true;
		}
		this->UnconsumeToken();
	}
	return false;
}

bool Parser::IsTypeName() {
	return 
	this->PeekToken("void") || 
	this->PeekToken("int32") || 
	this->PeekToken("char");
}

// Parse: int64, string....

ASTNode *Parser::ParseBaseType() {
	//ASTNode *node = new ASTNode;
	if(this->IsTypeName()) {
		this->ExpectToken(TT_KEYWORD);
	} else {
		throw string("not a type");
	}
	return NULL;
}

// Parse: myFunc(expr, expr, ...)

ASTNode *Parser::ParseCall() {
	ASTCall *node = new ASTCall;
	node->name = this->token.value;
	this->ExpectToken(TT_KEYWORD);
	this->ExpectToken("(");
	node->args = this->ParseArguments();
	this->ExpectToken(")");
	return node;
}

// (type x = expr)

ASTNode *Parser::ParseStmt() {
	ASTStmt *node = new ASTStmt;
	if(this->PeekToken("while")) {
		this->ExpectToken("while");
		this->ExpectToken("(");
		this->ParseExpr();
		this->ExpectToken(")");
		this->ParseStmt();
	} else if(this->PeekToken("{")) {
		ASTBlock *block = new ASTBlock;

		this->scope->PushScope(); // Push frame

		this->ExpectToken("{");
		while(!this->PeekToken("}")) {
			block->stmt.push_back((ASTNode*)this->ParseStmt());
		}
		this->ExpectToken("}");

		this->scope->PopScope(); // pop frame

		return block;
	} else if(this->IsTypeName()) {
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

// function () { stmt }

ASTNode *Parser::ParseFunction() {
	ASTFunction *node = new ASTFunction;

	this->scope->PushScope(); // Push frame

	this->ParseBaseType();
	node->name = this->token.value;
	this->ExpectToken(TT_KEYWORD);
	this->ExpectToken("(");
	node->params = this->ParseParameters();
	this->ExpectToken(")");
	this->ExpectToken("{");
	// Parse Body
	while(!this->PeekToken("}")) {
		node->stmt.push_back((ASTNode*)this->ParseStmt());
	}
	this->ExpectToken("}");

	this->scope->PopScope(); // pop frame
	return node;
}

// (type x) or (type x = expr)

ASTNode *Parser::ParseDecl() {
	ASTDecl *node = new ASTDecl;
	this->ParseBaseType();
	if(this->scope->ContainsVar(this->token.value)) {
		throw string("variable '" + this->token.value + "' already defined");
	}
	this->scope->InsertVar(this->token.value);
	node->name = this->token.value;
	this->ExpectToken(TT_KEYWORD);
	if(this->ConsumeToken("=")) {
		node->body = this->ParseExpr();
	}
	return node;
}

ASTNode *Parser::start() {
	ASTProgram *node = new ASTProgram;
	while(!this->PeekToken(TT_EOF)) {
		node->functions.push_back(this->ParseFunction());
	}
	return node;
}

Parser::~Parser() {
	delete this->scope;
}