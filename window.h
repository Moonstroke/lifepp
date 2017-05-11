#ifndef WINDOW_INCLUDED
#define WINDOW_INCLUDED

#include <iostream>

typedef unsigned int uint; // convenience for shorter type 

class Window {
private:
	
	uint w, h;
	uint x, y;
	WINDOW* win;

public:
	Window(uint, uint, uint, uint, bool);
	
	~Window();
	
	void dim(uint&, uint&);
	void pos(uint&, uint&);
	
	void refresh();
	
	
};

#endif
