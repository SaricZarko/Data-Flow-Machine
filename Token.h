#ifndef _TOKEN_H
#define _TOKEN_H
#include<string>
#include<vector>
#include"Exception.h"
using namespace std;

class Operator;

class Token
{
public:
	Token() :name_(""), operation_(nullptr), value_(0.0), timeDelay_(0), id_(""), function_(""), startTime_(0),
	 endTime_(0){}
	string getName() { return this->name_; }
	void setName(string name) { this->name_ = name; }
	Operator* getOperator() { return this->operation_; }
	void setOperator(Operator* op) { this->operation_ = op; }
	void setValue(double val) { this->value_ = val; }
	double getValue() { return this->value_; }
	void setOperands(string nam) { this->operands_.push_back(nam); };
	vector<string>getOperands() { return this->operands_; }
	void WriteInOperands(int k, string s) { this->operands_[k] = s; }
	void setTimeDel(int del) { this->timeDelay_.push_back(del); }
	vector<int> getTimeDel() { return this->timeDelay_; }
	string getId() { return this->id_; }
	void setId(string id) { this->id_ = id; }
	string getFunction() { return this->function_; }
	void setFunction(string fun) { this->function_ = fun; }
private:
	friend class Machine;
	string name_;
	Operator* operation_;
	double value_;
	vector<string> operands_;
	vector<int> timeDelay_;
	string id_;
	string function_;
	int startTime_;
	int endTime_;
};
#endif // !_TOKEN_H
