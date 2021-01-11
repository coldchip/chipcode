#include "scope.h"

Scope::Scope() {

}

void Scope::PushScope() {
	VarList list;
	this->scope.push(list);
}

int Scope::GetOffset() {
	return this->scope.top().offset;
}

void Scope::InsertVar(string value) {
	Var var;
	var.value = value;
	VarList &current = this->scope.top();
	var.offset = current.offset;
	current.offset += 4;
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

int Scope::GetVarOffset(string value) {
	Var var;
	var.value = value;
	VarList &current = this->scope.top();
	for(Var &var : current.list) {
		if(var.value.compare(value) == 0) {
			return var.offset;
		} 
	}
	throw string(value + " not found in scope");
}

void Scope::PopScope() {
	this->scope.pop();
}

Scope::~Scope() {

}