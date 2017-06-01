#include <ncurses.h>
#include "window.h"
#include "board.h"

#define unsigned int uint

Window::Window(uint inner_width, uint inner_height, uint xpos, uint ypos, bool center, bool do_keypad) : w(inner_width + 2), h(inner_height + 2), x(center ? (x - w) / 2 : x), y(center ? (y - h) / 2 : y), win(newwin(h, w, x, y)) {
	keypad(win, do_keypad);
}

Window::del() {
	delwin(win); //à vérifier
	delete win;
}

Window::Window(const Window &window) : w(window.w), h(window.h), x(window.x), y(window.y), win(dupwin(window.wiw)) {}

Window::~Window() {
	wborder(win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '); // effacer la bordure de la fenêtre
	del();
	win = nullptr;
}

Window& Window::operator=(const Window &window) {
	w(window.w);
	h(window.h);
	x(window.x);
	y(window.y);
	del();
	win(dupwin(window.wiw));
}

void Window::get_pos(uint& x, uint& y) {
	x = x;
	y = y;
}

void Window::get_dim(uint& width, uint& height) {
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

void Window::mvprintw(const std::string str, uint i, uint j) const {
	mvwprintw(win, j, i, "%s", str.c_str());
}

void Window::printw(const Board *b) const {
	uint w, h;
	b->get_dim(w, h);
	for(uint j(0); j < h; ++j)
		for(uint i(0); i < w; ++i)
			mvwaddch(win, j + 1, i + 1, b->at(i, j));
}
