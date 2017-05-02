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
	Board(int, int, char, char, char);
	
	~Board();
	
	void dim(int&, int&) const;
	
	bool operator()(int, int) const;
	
	int neighbors(int, int) const;
	
	void toggle(int, int);
	
	bool nextstate(int, int);
	
	void nextgen();
	
	friend std::ostream& operator<<(std::ostream&, const Board&);
	
	std::string tostring() const;
};


#endif
