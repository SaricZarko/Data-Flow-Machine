#include "Compiler.h"

Compiler::Compiler(string filepath)
{
	ifstream file(filepath);
	while (!file.eof()) {
		string tmp, tmp2 = "", tmp3 = "";
		int i = 0;
		getline(file, tmp);
		while (tmp[i] == ' ')i++;
		while (tmp[i] != '=') {
			if (tmp[i] == ' ') { i++; continue; }
			tmp2 += tmp[i++];
		}
		while (tmp[i] == ' ' || tmp[i] == '=')i++;//ucitao si sva vremena ovde
		if (isdigit(tmp[i])) {
			while (isdigit(tmp[i]))tmp3 += tmp[i++];
			if (tmp2 == "Ta")
				this->Ta_ = stoi(tmp3);
			else if (tmp2 == "Tm")
				this->Tm_ = stoi(tmp3);
			else if (tmp2 == "Te")
				this->Te_ = stoi(tmp3);
			else if (tmp2 == "Tw")
				this->Tw_ = stoi(tmp3);
			else  this->Nw_ = stoi(tmp3);

		}
		else {//ucitavas koja je vrsta strategije tu
			for (int j = i; j < tmp.size(); j++) {
				tmp3 += tmp[i++];
			}
			this->strategyType_ = tmp3;
		}

	}
	if (strategyType_ == "simple") {
		Strategy* strategija = new SimpleStrategy();
		strategija->execute();
		toks = strategija->tokens;
	}
}

Compiler::~Compiler()
{
	for (int i = 0; i < toks.size(); i++) {
		delete toks[i];
	}
}

int Strategy::powerOfOperator(const string& c)
{
	if (c == "^")return 4;
	else if (c == "*")return 3;
	else if (c == "+")return 2;
	else if (c == "=")return 1;
	else return 0;
}

bool Strategy::isOperator(const string& c)
{

	if (c == "^")return true;
	else if (c == "*")return true;
	else if (c == "+")return true;
	else if (c == "=")return true;
	else return false;
}

void Strategy::createTokens(int& num, int& counter)
// razmisli jos malo oko ideje za razlicit operacije apstraktne normalne i dodele mozda bude bolje nego da kalemis na kvarno!!!!!!!!!!!!!!!!
{

	while (this->program.size() != 1) {
		string maxVal = "";
		int delPlace = 0;
		for (int i = 0; i < program.size(); i++) {
			if (powerOfOperator(program[i]) > powerOfOperator(maxVal)) {
				maxVal = program[i];
				delPlace = i;
			}
		}
		Operator* temp = opType(maxVal);
		if (temp->getAssociativity() != "associative") {
			for (int i = delPlace; i < program.size(); i++) {
				while (i < program.size() && !isOperator(program[i]))i++;
				if (i < program.size() && isOperator(program[i]) && powerOfOperator(maxVal) == powerOfOperator(program[i]))delPlace = i;
				else break;
			}
		}
		Token* newToks = new Token();
		newToks->setOperator(temp);
		if (maxVal == "=") {
			newToks->setName(program[delPlace - 1]);
			newToks->setOperands(program[delPlace + 1]);
		}
		else {
			newToks->setName("t" + to_string(num++));
			newToks->setOperands(program[delPlace - 1]);
			newToks->setOperands(program[delPlace + 1]);
		}
		newToks->setId("[" + to_string(counter++) + "]");
		tokens.push_back(newToks);
		int begin = delPlace - 1;
		int end = delPlace + 2;
		workWithString(begin, end);

	}
	program.erase(program.begin(), program.end());
}

void Strategy::workWithString(int i, int j)// samo je jos ostalo da resis probleme sa mestima ovo ostalo je sve okej
{
	vector<string> tmp;
	for (int p = 0; p < i; p++) {
		tmp.push_back(this->program[p]);
	}
	tmp.push_back(tokens.back()->getName());
	for (int p = j; p < program.size(); p++) {
		tmp.push_back(this->program[p]);
	}
	program.erase(program.begin(), program.end());
	program = tmp;

}

Operator* Strategy::opType(const string& st)
{
	if (st == "^") {
		Operator* temp = new Pow();
		return temp;
	}
	else if (st == "*") {
		Operator* temp = new Mul();
		return temp;
	}
	else if (st == "+") {
		Operator* temp = new Add();
		return temp;
	}
	else if (st == "=") {
		Operator* temp = new Eq();
		return temp;
	}
	else {
		return nullptr;
	}
}




void Strategy::operatorFound(const string& place, const string& what, vector<int>& posit)
{
	int counter = 0;
	int pos = place.find(what);
	while (pos != -1) {
		posit.push_back(pos);
		pos = place.find(what, pos + 1);
	}
	sort(posit.begin(), posit.end());

}

void Strategy::revSort(vector<int>& ints)
{
	int tem = 0;
	for (int i = 0; i < ints.size() - 1; i++) {
		for (int j = i + 1; j < ints.size(); j++) {
			if (ints[i] > ints[j]) {
				tem = ints[i];
				ints[i] = ints[j];
				ints[j] = tem;
			}
		}
	}
}





void SimpleStrategy::execute()
{
	int counter = 1, counter1 = 1;
	ifstream file("test.txt");
	while (!file.eof()) {
		string tmp, tmp2;
		int  sum = 0, j = 0, kp = 0;
		getline(file, tmp);
		Token* tempToken = new Token();
		for (int j = 0; j < tmp.size(); j++) {
			if (tmp[j] == ' ') continue;
			tmp2 += tmp[j];
		}
		vector<int>pos;
		operatorFound(tmp2, "=", pos);
		operatorFound(tmp2, "^", pos);
		operatorFound(tmp2, "*", pos);
		operatorFound(tmp2, "+", pos);
		revSort(pos);
		vector<int> posEnd;
		for (int i = 0; i < pos.size(); i++) {//na kraju sam jebenih zivaca sa ovim kurcem od ucitavanja probaj jos jednom ako smislis nesto ujutru normalno ako ne kalemi brt moj ko mu jebe mamu u picku
			int place = pos[i];
			string nejm;
			nejm += tmp2[place];
			while (!isOperator(nejm)) nejm += tmp[place++];
			posEnd.push_back(place);
		}
		int kick = 0;
		for (int cnt = 0; cnt < tmp2.size();) {
			string nejm;
			string put;
			if (kick < pos.size()) {
				while (cnt < tmp2.size() && cnt != pos[kick])put += tmp2[cnt++];
				program.push_back(put);
				for (cnt = pos[kick]; cnt <= posEnd[kick]; cnt++) {
					nejm += tmp2[cnt];
				}
				program.push_back(nejm);
				kick++;
			}
			else {
				while (cnt < tmp2.size())
					put += tmp2[cnt++];
				program.push_back(put);
			}
		}
		createTokens(counter, counter1);
	}
	ofstream myfile("test.imf");
	int numbers = 1;
	for (int i = 0; i < tokens.size(); i++) {
		myfile << "[" + to_string(numbers++) + "]" << " " << tokens[i]->getOperator()->getOperationType() << " " << tokens[i]->getName() << " ";
		for (int j = 0; j < tokens[i]->getOperands().size(); j++) {
			myfile << tokens[i]->getOperands()[j] << " ";
		}
		myfile << endl;
	}
}