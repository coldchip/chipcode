#include "parser.h"

void Parser::PushStack() {
	this->stack.push_back(vector<Var>());
}

void Parser::AddVar(string value) {
	Var var;
	var.value = value;
	vector<Var> &current = this->stack.back();
	current.push_back(var);
}

bool Parser::HasVar(string value) {
	Var var;
	var.value = value;
	vector<Var> current = this->stack.back();
	for(Var &var : current) {
		if(var.value.compare(value) == 0) {
			return true;
		} 
	}
	return false;
}

void Parser::PopStack() {
	this->stack.pop_back();
}