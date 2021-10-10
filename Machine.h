#ifndef _MACHINE_H
#define _MACHINE_H
#include"Compiler.h"
class Machine {

public:
	Machine(Compiler* name) {
		Memorija::getInstance()->setNw(name->Nw_);
		this->Ta_ = name->Ta_;
		this->Tm_ = name->Tm_;
		this->Te_ = name->Te_;
		this->Tw_ = name->Tw_;
		tok_ = name->toks;
	}
	void exec(string filename);
	bool isReady(Token* rdy);
	int getInfo(string type);
	string OperatorFunctionType(Token* typ);
	void updateToks();
	void tokensCompleted();
	bool isTokenRdy(Token* rdy);
	void update(Token* updater);
	void write(ofstream& filename);
	void sortDone();
	void updateTimetable(Token* updater);
	bool isDouble(const string& st);
private:
	int Ta_, Tm_, Te_, Tw_;
	vector<Token*> executing_, waiting_, completed_;
	vector<Token*> tok_;
};

#endif // !_MACHINE_H*/