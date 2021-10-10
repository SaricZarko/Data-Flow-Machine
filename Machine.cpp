#include "Machine.h"

void Machine::exec(string filename)
{
	int startTime = 0, endTime = 0;
	string mem, txt;
	mem = filename + ".mem";
	txt = filename + ".log";
	ofstream file1(mem);
	ofstream file2(txt);
	vector<Token*> temporary;
	for (int i = 0; i < this->tok_.size(); i++) {
		tok_[i]->operation_->setDelay(getInfo(tok_[i]->operation_->getDelayType()));
		tok_[i]->endTime_= tok_[i]->operation_->getDelay();
		if (isReady(tok_[i]))executing_.push_back(tok_[i]);
		else this->waiting_.push_back(tok_[i]);
	}
	while (!waiting_.empty()) {
		vector<int> disposing;
		for (int j = 0; j < waiting_.size(); j++) {
			if (isReady(waiting_[j])) {
				executing_.push_back(waiting_[j]);
				waiting_.erase(waiting_.begin() + j);
			}
		}
		int i = 0;
		for (i = 0; i < Memorija::getInstance()->getNw_(); i++) {
			if (i == executing_.size())break;
			this->completed_.push_back(executing_[i]);
			disposing.push_back(i);
		}
		for (int j = 0; j < completed_.size(); j++) {
			completed_[j]->operation_->operate(completed_[j]->name_,completed_[j]->operands_[0]);
			endTime = completed_[j]->endTime_;
		}
		updateToks();
		Token* tmp = completed_[0];
		for (int i = 0; i < disposing.size(); i++) {
			executing_.erase(executing_.begin());
		}
		updateTimetable(tmp);
		tokensCompleted();	
		temporary.insert(temporary.end(), completed_.begin(), completed_.end());
		completed_.erase(completed_.begin(), completed_.end());
		}//treba jos napraviti update za waiting i tokeni kako se izbacujuj i update !!
	completed_ = temporary;
	write(file2);
	Memorija::getInstance()->memMake(file1);
}

bool Machine::isReady(Token* rdy)
{
	rdy->function_=this->OperatorFunctionType(rdy);
	if (rdy->getFunction() != "assign-ready")return false;
	else return true;
}

int Machine::getInfo(string type)
{
	if (type == "Ta")
		return this->Ta_;
	else if (type == "Tm")
		return this->Tm_;
	else if (type == "Te")
		return this->Te_;
	else if (type == "Tw")
		return this->Tw_;
	else return 0;

}

string Machine::OperatorFunctionType(Token* typ)
{
	bool count = true;
	if (typ->operation_->getOperationType() == "=") {
		for (int i = 0; i < typ->operands_.size(); i++) {
			if (!isDouble(typ->operands_[i])) {
				count = false;
				break;
			}
		}
		if (count)return"assign-ready";
		else return"assign-waiting";
	}
	else return "token";
}

void Machine::updateToks()//nakon upisivanja u memoriju dal je neki token spreman
{

	for (int j = 0; j < waiting_.size(); j++) {
		for (int k = 0; k < waiting_[j]->operands_.size(); k++) {
			try {
				waiting_[j]->operands_[k]= to_string(Memorija::getInstance()->get(waiting_[j]->operands_[k]));
			}
			catch (VarNotAvailableException * se) {
				cout << se->what() << endl;
			}
		}
	}
}

void Machine::tokensCompleted()
{
	for (int i = 0; i < waiting_.size();) {
		try{
			if (isTokenRdy(waiting_[i]) && OperatorFunctionType(waiting_[i]) == "token") {
				waiting_[i]->value_=waiting_[i]->operation_->operate(waiting_[i]->operands_[0], waiting_[i]->operands_[1]);
				completed_.push_back(waiting_[i]);
				Token* tmp = waiting_[i];
				waiting_.erase(waiting_.begin() + i);	
				update(tmp);
				i = 0;
			}
			else i++;
		}
		catch (TokenNotReady * se) {
			cout << se->what() << endl;
		}
	}
}

bool Machine::isTokenRdy(Token* rdy)
{
	for (int i = 0; i < rdy->operands_.size(); i++) {
		if (isDouble(rdy->operands_[i])) continue;
		else return false;
	}
	return true;
}

void Machine::update(Token* updater)
{
	for (int i = 0; i < waiting_.size(); i++) {
		for (int j = 0; j < waiting_[i]->operands_.size(); j++) {
			if (waiting_[i]->operands_[j] == updater->name_) {
				waiting_[i]->WriteInOperands(j, to_string(updater->getValue()));
					waiting_[i]->startTime_ = updater->endTime_;
					waiting_[i]->endTime_ = waiting_[i]->operation_->getDelay() + updater->endTime_;
			}
		}
	}
}

void Machine::write(ofstream& filename)
{
	sortDone();
	for (int i = 0; i < completed_.size(); i++) {
		filename << completed_[i]->getId() << " " << "(" << completed_[i]->startTime_ << "-" << completed_[i]->endTime_ << ")ns" << endl;
	}
}

void Machine::sortDone()
{
	Token* temp;
	for (int i = 0; i < this->completed_.size() - 1; i++) {
		for (int j = i + 1; j < this->completed_.size(); j++) {
			if (completed_[i]->startTime_ > completed_[j]->startTime_) {
				temp = completed_[i];
				completed_[i] = completed_[j];
				completed_[j] = temp;
			}
			else if (completed_[i]->startTime_ == completed_[j]->startTime_) {
				if (completed_[i]->endTime_ > completed_[j]->endTime_) {
					temp = completed_[i];
					completed_[i] = completed_[j];
					completed_[j] = temp;
				}
			}
		}
	}
}

void Machine::updateTimetable(Token* updater) {
	if (updater->function_ == "assign-ready") {
		for (int i = 0; i < waiting_.size(); i++) {
				waiting_[i]->startTime_ = updater->endTime_;
				waiting_[i]->endTime_ = waiting_[i]->operation_->getDelay() + waiting_[i]->startTime_;
		}
		for (int i = 0; i < executing_.size(); i++) {
			executing_[i]->startTime_ = updater->endTime_;
			executing_[i]->endTime_ = executing_[i]->operation_->getDelay() + updater->endTime_;
		}
	}
}

bool Machine::isDouble(const string& st)
{	
	for (int i = 0; i < st.size(); i++) {
		if (st[i] == '.' || isdigit(st[i])|| st[i]=='-')continue;
		else return false;
	}
	return true;
}
