#include "parser.h"

Parser::Parser(vector<Token> tokens) {
	this->tokens = tokens;
	this->il = tokens.begin();
	this->token = *this->il;
}

void Parser::NextToken() {
	this->il++;
	this->token = *this->il;
}

void Parser::AssertToken(string d) {
	if(this->token.value.compare(d) != 0) {
		throw string("Unable to parse");
	}
}

void Parser::AssertToken(TokenType type) {
	if(this->token.type != type) {
		throw string("Unable to parse");
	}
}

bool Parser::IsToken(string d) {
	return (this->token.value.compare(d) == 0);
}

bool Parser::IsToken(TokenType type) {
	return (this->token.type == type);
}

void Parser::start() {
	cout << "-----Parser-----" << endl;
	cout << "Type: " << this->token.type << endl;
	cout << "value: " << this->token.value << endl;

	this->AssertToken("function"); this->NextToken();
	this->AssertToken(TT_KEYWORD); this->NextToken();
	this->AssertToken("("); this->NextToken();
	this->AssertToken(")"); this->NextToken();
	this->AssertToken("{"); this->NextToken();
	// Parse Body
	this->AssertToken("}"); this->NextToken();
}

Parser::~Parser() {

}