#include"Machine.h"
Memorija* Memorija::instance = 0;
int main() {
	Compiler* comp = new Compiler("config.txt");
	Machine* mac = new Machine(comp);
	mac->exec("test");
}