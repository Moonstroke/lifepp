#ifndef WINDOW_INCLUDED
#define WINDOW_INCLUDED

#include <curses.h>
#include <iostream>
typedef uint unsigned int; // convenience for shorter type 

class Window {
private:
	
	uint width, height;
	uint x, y;

public:
	Window(uint w, uint h, uint x, uint y, bool center = false);
	
	~Window();
	
	void pos(&x, &y);
	
	void refresh();
	
	
};

#endif
