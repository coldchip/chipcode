#ifndef SCOPE_H
#define SCOPE_H

#include <stack>
#include <vector>
#include <string>

using namespace std;

typedef struct _Var {
	string value;
} Var;

typedef struct _VarList {
	vector<Var> list;
} VarList;

class Scope {
	public:
		Scope();
		void PushScope();
		void InsertVar(string value);
		bool ContainsVar(string value);
		void PopScope();
		~Scope();
	private:
		stack<VarList> scope;
};

#endif