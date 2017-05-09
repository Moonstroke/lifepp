#include <ncurses.h>
#include "board.h"

Window(uint width, uint height, uint x, uint y, bool center = false) : w(width), h(height), x(x), y(y) {
	
}

~Window() {
	
}

void pos(&x, &y) {
	x = this->x;
	y = this->y;
}

void dim(&w,idth, &height) {
	width = this->w;
	height = this->h;
}

void refresh() {
	wrefresh(this->win);
}
