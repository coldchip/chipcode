#include "parser.h"

ASTNode *Parser::ParseExpr() {
	return this->ParseAssign();
}

ASTNode *Parser::ParseAssign() {
	ASTNode *left = this->ParsePlus();
	if(this->ConsumeToken("=")) {
		ASTBinaryExpr *node = new ASTBinaryExpr;
		node->left = left;
		node->right = this->ParseAssign();
		return node;
	}
	return left;
}

ASTNode *Parser::ParsePlus() {
	ASTNode *left = this->ParseMinus();
	if(this->ConsumeToken("+")) {
		ASTBinaryExpr *node = new ASTBinaryExpr;
		node->left = left;
		node->right = this->ParsePlus();
		return node;
	}
	return left;
}

ASTNode *Parser::ParseMinus() {
	ASTNode *left = this->ParseMultiply();
	if(this->ConsumeToken("-")) {
		ASTBinaryExpr *node = new ASTBinaryExpr;
		node->left = left;
		node->right = this->ParseMinus();
		return node;
	}
	return left;
}

ASTNode *Parser::ParseMultiply() {
	ASTNode *left = this->ParseDivide();
	if(this->ConsumeToken("*")) {
		ASTBinaryExpr *node = new ASTBinaryExpr;
		node->left = left;
		node->right = this->ParseMultiply();
		return node;
	}
	return left;
}

ASTNode *Parser::ParseDivide() {
	ASTNode *left = this->ParseEquality();
	if(this->ConsumeToken("/")) {
		ASTBinaryExpr *node = new ASTBinaryExpr;
		node->left = left;
		node->right = this->ParseDivide();
		return node;
	}
	return left;
}

ASTNode *Parser::ParseEquality() {
	ASTNode *left = this->ParsePrimary();
	if(this->ConsumeToken("==")) {
		ASTBinaryExpr *node = new ASTBinaryExpr;
		node->left = left;
		node->right = this->ParseEquality();
		return node;
	}
	return left;
}

ASTNode *Parser::ParsePrimary() {
	Token token = this->token;
	if(this->ConsumeToken(TT_KEYWORD)) {
		if(!this->HasVar(token.value)) {
			throw string("variable '" + token.value + "' does not exist on the scope");
		}
		ASTIdentifier *node = new ASTIdentifier;
		node->value = token.value;
		return node;
	} else if(this->ConsumeToken(TT_NUMBER)) {
		ASTLiteral *node = new ASTLiteral;
		cout << token.value << endl;
		node->value = stoi(token.value);
		return node;
	} else {
		throw string("Expecting TT_KEYWORD or TT_NUMBER");
	}
}