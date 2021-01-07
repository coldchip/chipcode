#include "parser.h"

void Parser::ParseExpr() {
	this->ParseAssign();
}

void Parser::ParseAssign() {
	this->ParsePlus();
	if(this->ConsumeToken("=")) {
		this->ParseAssign();
	}
}

void Parser::ParsePlus() {
	this->ParseMinus();
	if(this->ConsumeToken("+")) {
		this->ParsePlus();
	}
}

void Parser::ParseMinus() {
	this->ParseMultiply();
	if(this->ConsumeToken("-")) {
		this->ParseMinus();
	}
}

void Parser::ParseMultiply() {
	this->ParseDivide();
	if(this->ConsumeToken("*")) {
		this->ParseMultiply();
	}
}

void Parser::ParseDivide() {
	this->ParseEquality();
	if(this->ConsumeToken("/")) {
		this->ParseDivide();
	}
}

void Parser::ParseEquality() {
	this->ParsePrimary();
	if(this->ConsumeToken("==")) {
		this->ParseEquality();
	}
}

void Parser::ParsePrimary() {
	if(this->ConsumeToken(TT_KEYWORD)) {

	} else if(this->ConsumeToken(TT_NUMBER)) {

	} else {
		throw string("Expecting TT_KEYWORD or TT_NUMBER");
	}
}