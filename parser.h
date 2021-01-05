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
};

#endif