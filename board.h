#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>

class Board {
private:
	std::vector<std::vector<bool>> cells;
	unsigned int h, w;
	char live, dead, wall;

public:
	Board(unsigned int, unsigned int, char, char, char);

	~Board();

	void get_dim(unsigned int&, unsigned int&) const;

	bool operator()(unsigned int, unsigned int) const;

	char at(uint i, uint j) const;

	int neighbors(unsigned int, unsigned int) const;

	void toggle(unsigned int, unsigned int);

	bool nextstate(unsigned int, unsigned int) const;

	void nextgen();

	friend std::ostream& operator<<(std::ostream&, const Board&);

	std::string tostring() const;
};


#endif
