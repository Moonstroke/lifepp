#include <sstream>
#include "board.h"


using namespace std;

string input(string prompt = "") {
	string res;
	cout << prompt;
	getline(cin, res);
	return res;
}

char char_input(string prompt = "") {
	char res;
	stringstream(input(prompt)) >> res;
	return res;
}

int int_input(string prompt = "") {
	int res;
	stringstream(input(prompt)) >> res;
	return res;
}

void getpos(string prompt, int& i, int &j) {
	cout << prompt;
	string inp;
	getline(cin, inp);
	stringstream(inp) >> i >> j;
}

int main(int argc, char *argv[]) {
	
	char live('@'), dead(' '), wall('#');
	
	int w(15), h(11);
	
	
	Board b(w, h, live, dead, wall);
	b.toggle(7, 4);
	b.toggle(6, 5);
	b.toggle(7, 5);
	b.toggle(8, 5);
	b.toggle(7, 6);
	
	cout << b;
	char action(tolower(char_input("Action? [S]tep /[t]oggle cell / [q]uit ")));
	bool loop(true);
	while(action != 'q') {
		if(action == 't') {
			int i(int_input("i = "));
			int j(int_input("j = "));
			b.toggle(i, j);
		}
		else b.step();
		cout << b;
		action = tolower(char_input("Action? [S]tep /[t]oggle cell / [q]uit "));
		cout << "action = " << action << endl;
	}
	return 0;
}
