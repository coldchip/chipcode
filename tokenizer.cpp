#include "tokenizer.h"

Tokenizer::Tokenizer(string input) {
	this->data = input;
	this->pos  = 0;
}

bool Tokenizer::IsKeyword(char bit) {
	return ('a' <= bit && bit <= 'z') || ('A' <= bit && bit <= 'Z') || bit == '_';
}

bool Tokenizer::IsNumber(char bit) {
	return ('0' <= bit && bit <= '9');
}

bool Tokenizer::IsSpace(char bit) {
	return (bit == '	' || bit == ' ' || bit == 0x0d || bit == 0x0a);
}

vector<Token> Tokenizer::start() {
	vector<Token> tokens;
	const char *p = this->data.c_str();
	while(*p != '\0') {
		if(this->IsKeyword(*p)) {
			string keyword = "";
			while(this->IsKeyword(*p)) {
				keyword.append(p, 1);
				p++;
			}
			Token token;
			token.type = TT_KEYWORD;
			token.value = keyword;
			tokens.push_back(token);
		} else if(this->IsNumber(*p)) {
			string number = "";
			while(this->IsNumber(*p)) {
				number.append(p, 1);
				p++;
			}
			Token token;
			token.type = TT_NUMBER;
			token.value = number;
			tokens.push_back(token);
		} else if(*p == '"') {
			p++;
			string str = "";
			while(*p != '"') {
				str.append(p, 1);
				p++;
			}
			p++;
			Token token;
			token.type = TT_STRING;
			token.value = str;
			tokens.push_back(token);
		} else if(*p == '\'') {
			p++;
			string str = "";
			while(*p != '\'') {
				str.append(p, 1);
				p++;
			}
			p++;
			Token token;
			token.type = TT_CHAR;
			token.value = str;
			tokens.push_back(token);
		} else if(IsSpace(*p)) {
			p++;
		} else {
			Token token;
			token.type = TT_TOKEN;
			token.value = string(1, *p);
			tokens.push_back(token);
			p++;
		}
	}
	return tokens;
}

Tokenizer::~Tokenizer() {

}