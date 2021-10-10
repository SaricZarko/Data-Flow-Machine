#ifndef _COMPILER_H_
#define _COMPILER_H_
#include "Operation.h"
class Compiler {

public:
	Compiler(string filepath);
	//string toExplicit(string implicit);
	//int powerOfOperator(char c);
	//string workWithString(string work, int a, int b);
	//int makeAlist(string filepath, int number);
	~Compiler();
private:
	friend class Machine;
	int Ta_, Tm_, Te_, Tw_, Nw_;
	string strategyType_;
	vector<Token*> toks;
};

class Strategy {

public:

	virtual void execute() = 0;
	int powerOfOperator(const string& c);
	bool isOperator(const string& c);
	void createTokens(int& num, int& counter);
	void workWithString(int i, int j);
	Operator* opType(const string& st);
	void operatorFound(const string& place, const string& what, vector<int>& posit);
	void revSort(vector<int>& ints);
	string OperatorFunctionType(Token* typ);
protected:
	friend class Compiler;
	vector<string> program;
	vector<Token*> tokens;
};
class SimpleStrategy : public Strategy {

public:
	virtual void execute() override;
};
class AdvancedStrategy : public Strategy {

public:
	virtual void execute() override;

};
#endif