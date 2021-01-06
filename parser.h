#ifndef PARSER_H
#define PARSER_H

#include "tokenizer.h"

using namespace std;

class Parser {
	public:
		Parser(vector<Token> tokens);
		void start();
		~Parser();
	private:
		vector<Token> tokens;
		Token token;
		vector<Token>::iterator il;

		void NextToken();
		void AssertToken(string type);
		void AssertToken(TokenType type);
		bool IsToken(string type);
		bool IsToken(TokenType type);
};

#endif