#include <ncurses.h>
#include "window.h"

#define unsigned int uint;

Window::Window(uint inner_width, uint inner_height, uint xpos, uint ypos, bool center, bool do_keypad) : w(inner_width + 2), h(inner_height + 2), x(center ? (x - w) / 2 : x), y(center ? (y - h) / 2 : y) {
	win = newwin(h, w, x, y);
	keypad(win, do_keypad);
}

Window::~Window() {
	win = nullptr;
}


void Window::pos(uint& x, uint& y) {
	x = x;
	y = y;
}

void Window::dim(uint& width, uint& height) {
	width = w;
	height = h;
}

void Window::draw(char hbord, char vbord) {
	box(this->win, hbord, vbord);
	this->refresh();
}

void Window::refresh() {
	wrefresh(win);
}

void Window::highlight(uint i, uint j, uint len) {
	mvwchgat(win, j + 1, i + 1, len, A_REVERSE, 0, NULL);
}

int Window::getch() {
	return wgetch(win);
}

void Window::printw(char str[]) {
	wprintw(win, str);
}

void Window::printw(std::string str) {
	wprintw(win, str.c_str());
}
