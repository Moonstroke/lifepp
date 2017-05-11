#include <ncurses.h>
#include "window.h"

Window::Window(uint width, uint height, uint x, uint y, bool center = false) : w(width), h(height), x(x), y(y) {
	
}

Window::~Window() {
	
}

void Window::pos(uint& x, uint& y) {
	x = x;
	y = y;
}

void Window::dim(uint& width, uint& height) {
	width = w;
	height = h;
}

void Window::refresh() {
	wrefresh(win);
}
