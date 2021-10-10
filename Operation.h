#ifndef _OPERATION_H
#define _OPERATION_H
#include"Memorija.h"

class Operator {

public:
	virtual double operate(string a, string b) = 0;
	string getOperationType() { return operationType_; };
	string getAssociativity() { return associativity_; }
	void setDelay(int n) { this->delay_ = n; }
	int getDelay() { return delay_; }
	string getDelayType() { return this->delayType_; }
protected:
	string associativity_;
	string operationType_;
	int delay_;
	string delayType_;
};
class Add :public Operator {

public:
	Add() {
		associativity_ = "associative";
		operationType_ = "+";
		this->delay_ = 0;
		delayType_ = "Ta";
	}
	virtual double operate(string a, string b) override {
		return stod(a) + stod(b);
	}
};
class Mul : public Operator {
public:
	Mul() {
		associativity_ = "associative";
		operationType_ = "*";
		this->delay_ = 0;
		delayType_ = "Tm";
	};
	virtual double operate(string a, string b) override {
		return  stod(a) * stod(b);;
	}
};

class Pow : public Operator {
public:
	Pow() {
		associativity_ = "right-associative";
		operationType_ = "^";
		this->delay_ = 0;
		delayType_ = "Te";
	}
	virtual double operate(string a, string b) override {
		return pow(stod(a), stod(b));
	}
};
class Eq : public Operator {
public:
	Eq() {
		associativity_ = "assignement";
		operationType_ = "=";
		this->delay_ = 0;
		delayType_ = "Tw";
	}
	virtual double operate(string a, string b) override {
		Memorija::getInstance()->set(a, stod(b));
		return 1;
	}
};


#endif // !_OPERATION_H