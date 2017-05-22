#ifndef WINDOW_H
#define WINDOW_H

#undef getch //tu soules !!
#undef mvaddch
#include <iostream>

class Window {
private:

	unsigned int x, y;
	WINDOW* win;

public:
	unsigned int w, h;

	Window(unsigned int, unsigned int, unsigned int, unsigned int, bool = false, bool = false);

	~Window();

	void get_dim(unsigned int&, unsigned int&);
	void get_pos(unsigned int&, unsigned int&);

	void draw(char = '\0', char = '\0');
	void refresh();

	void highlight(unsigned int, unsigned int, unsigned int);

	int getch();

	void mvaddch(unsigned int, unsigned int, char);

	void printw(char[]);
	void printw(std::string);

};

#endif
