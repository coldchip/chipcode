#include "scope.h"

Scope::Scope() {

}

void Scope::PushScope() {
	VarList list;
	this->scope.push(list);
}

void Scope::InsertVar(string value) {
	Var var;
	var.value = value;
	VarList &current = this->scope.top();
	current.list.push_back(var);
}

bool Scope::ContainsVar(string value) {
	Var var;
	var.value = value;
	VarList &current = this->scope.top();
	for(Var &var : current.list) {
		if(var.value.compare(value) == 0) {
			return true;
		} 
	}
	return false;
}

void Scope::PopScope() {
	this->scope.pop();
}

Scope::~Scope() {

}