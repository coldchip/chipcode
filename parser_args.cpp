#include "parser.h"

ASTNode *Parser::ParseParameter() {
	ASTIdentifier *ident = new ASTIdentifier;
	this->ParseBaseType();
	ident->value = this->token.value;
	this->ExpectToken(TT_KEYWORD);
	return ident;
}

// Parse: a, b, ...

ASTNode *Parser::ParseParameters() {
	ASTParams *node = new ASTParams;
	if(this->PeekToken(")")) {
		return node;
	}

	node->params.push_back(this->ParseParameter());

	while(!this->PeekToken(")")) {
		this->ExpectToken(",");
		node->params.push_back(this->ParseParameter());
	}

	return node;
}

// Parse: expr, expr, ...

ASTNode *Parser::ParseArgument() {
	ASTIdentifier *ident = new ASTIdentifier;
	ident->value = this->token.value;
	this->ExpectToken(TT_KEYWORD);
	return ident;
}

// Parse: expr, expr, ...

ASTNode *Parser::ParseArguments() {
	ASTArgs *node = new ASTArgs;
	
	if(this->PeekToken(")")) {
		return node;
	}

	node->args.push_back(this->ParseArgument());

	while(!this->PeekToken(")")) {
		this->ExpectToken(",");
		node->args.push_back(this->ParseArgument());
	}

	return node;
}