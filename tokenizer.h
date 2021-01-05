#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

typedef enum {
	TT_EOF,
	TT_STRING,
	TT_CHAR,
	TT_NUMBER,
	TT_KEYWORD,
	TT_TOKEN
} TokenType;

typedef struct _Token {
	string value;
	TokenType type;
	int line;
	int col;
} Token;

class Tokenizer {
	public:
		Tokenizer(string input);
		vector<Token> start();
		~Tokenizer();
	private:
		string data;
		unsigned pos = 0;

		bool IsKeyword(char bit);
		bool IsNumber(char bit);
		bool IsSpace(char bit);
};

#endif