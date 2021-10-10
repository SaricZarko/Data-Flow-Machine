#ifndef _MEMORIJA_H
#define _MEMORIJA_H
#include<math.h>
#include<fstream>
#include<vector>
#include<algorithm>
#include"Token.h"
struct Mem {
	string name_;
	double val_;
};
class Memorija {

public:

	Memorija(const Memorija&) = delete;
	Memorija& operator=(const Memorija&) = delete;
	static Memorija* getInstance() {
		if (!instance)
			instance = new Memorija;
		return instance;
	}
	void set(string varName, double val);
	double get(string varName);
	void setNw(int n);
	vector<Mem*> getTok() { return this->memTokens; }
	void setTok(Mem* tmp) { this->memTokens.push_back(tmp); }
	int getNw_() { return this->Nw_; }
	void memMake(ofstream& filename);
private:

	static Memorija* instance;
	Memorija() = default;
	vector<Mem*> memTokens;
	int Nw_;
};


#endif