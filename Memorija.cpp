#include "Memorija.h"

void Memorija::set(string varName, double val)
{
	Mem* temp = new Mem();
	temp->name_ = varName;
	temp->val_ = val;
	Memorija::getInstance()->setTok(temp);
}

double Memorija::get(string varName)
{

	for (int i = 0; i < Memorija::getInstance()->getTok().size(); i++)
		if (Memorija::getInstance()->getTok()[i]->name_ == varName) {
			return Memorija::getInstance()->getTok()[i]->val_;
		}
	throw new VarNotAvailableException("Promenljiva jos uvek nije u memoriji");

}

void Memorija::setNw(int n)
{
	this->Nw_ = n;
}

void Memorija::memMake(ofstream& filename)
{
	for (int i = 0; i < Memorija::getInstance()->memTokens.size(); i++) {
		filename << Memorija::getInstance()->memTokens[i]->name_ << " = " << Memorija::getInstance()->memTokens[i]->val_ << endl;
	}
}

/*void Memorija::writeLog(Token* line, ofstream& filename,int& start,int& end)
{
	filename << line->getId() << " " << "(" << start << "-" << end << ")ns"<<endl;
}*/