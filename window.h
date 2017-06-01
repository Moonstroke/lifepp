#ifndef WINDOW_H
#define WINDOW_H

#undef getch //tu soules !!
#undef mvprintw

#include <iostream>
#include "board.h"

class Window {
private:

	unsigned int x, y;
	WINDOW* win;

	void del();
	
public:
	unsigned int w, h;

	Window(unsigned int, unsigned int, unsigned int, unsigned int, bool = false, bool = false);
	Window(const Window&);

	Window& operator=(const Window&);

	~Window();

	void get_dim(unsigned int&, unsigned int&);
	void get_pos(unsigned int&, unsigned int&);

	void draw(char = '\0', char = '\0');
	void refresh();

	void highlight(unsigned int, unsigned int, unsigned int);

	int getch();

	void mvprintw(const std::string, uint, uint) const;
	void printw(const Board*) const;
};

#endif
