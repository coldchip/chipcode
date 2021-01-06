#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>
#include "tokenizer.h"
#include "parser.h"

using namespace std;

int main(int argc, char const *argv[]) {
	/* code */

	std::ifstream t("code.txt");
	std::string input((std::istreambuf_iterator<char>(t)),  std::istreambuf_iterator<char>());

	try {
		Tokenizer tokenizer(input);
		vector<Token> tokens = tokenizer.start();

		for(Token token : tokens) {
			cout << "Type: " << token.type << endl;
			cout << "value: " << token.value << endl;
			cout << "--------------------------------" << endl;
		}


		Parser parser(tokens);
		parser.start();
	} catch(string &e) {
		cout << "Error: " << e << endl;
	}

	return 0;
}