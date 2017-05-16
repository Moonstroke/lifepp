#ifndef WINDOW_H
#define WINDOW_H

#undef getch //tu soules !!
#include <iostream>

class Window {
private:

	unsigned int x, y;
	WINDOW* win;

public:
	unsigned int w, h;

	Window(unsigned int, unsigned int, unsigned int, unsigned int, bool = false, bool = false);

	~Window();

	void dim(unsigned int&, unsigned int&);
	void pos(unsigned int&, unsigned int&);

	void draw(char = '\0', char = '\0');
	void refresh();

	void highlight(unsigned int, unsigned int, unsigned int);

	int getch();

	void printw(char[]);
	void printw(std::string);

};

#endif
