#ifndef WINDOW_H
#define WINDOW_H

#undef getch //tu soules !!
#include <iostream>

typedef unsigned int uint; // convenience for shorter type

class Window {
private:

	uint x, y;
	WINDOW* win;

public:
	uint w, h;

	Window(uint, uint, uint, uint, bool);

	~Window();

	void dim(uint&, uint&);
	void pos(uint&, uint&);

	void draw(char, char);
	void refresh();

	void highlight(uint, uint, uint);

	int getch();

	void printw(char[]);
	void printw(std::string);

};

#endif
