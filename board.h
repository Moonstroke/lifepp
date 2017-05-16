#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>

class Board {
private:
	std::vector<std::vector<bool>> cells;
	int h, w;
	char live, dead, wall;

public:
	Board(int, int, char, char, char);

	~Board();

	void dim(int&, int&) const;

	bool operator()(int, int) const;

	int neighbors(int, int) const;

	void toggle(int, int);

	bool nextstate(int, int) const;

	void nextgen();

	friend std::ostream& operator<<(std::ostream&, const Board&);

	std::string tostring() const;
};


#endif
