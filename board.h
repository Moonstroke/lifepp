#ifndef BOARD_INCLUDED
#define BOARD_INCLUDED

#include <iostream>
#include <vector>

class Board {
private:
	std::vector<std::vector<bool>> cells;
	int height, width;
	char livechar, deadchar, wallchar;

public:
	Board(int width, int height, char live, char dead, char wall);
	
	~Board();
	
	bool operator()(int i, int j) const;
	
	int neighbors(int i, int j) const;
	
	void toggle(int i, int j);
	
	bool nextstate(int i, int j);
	
	void step();
	
	friend std::ostream& operator<<(std::ostream&, const Board&);
	
};

#endif
