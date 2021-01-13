#ifndef SCOPE_H
#define SCOPE_H

#include <vector>
#include <string>

using namespace std;

typedef struct _Var {
	int offset;
	string value;
} Var;

typedef struct _VarList {
	int offset = 0;
	vector<Var> list;
} VarList;

class Scope {
	public:
		Scope();
		void PushScope();
		int GetOffset();
		void InsertVar(string value);
		bool ContainsVar(string value);
		int GetVarOffset(string value);
		void PopScope();
		~Scope();
	private:
		vector<VarList> scope;
};

#endif