#include "board.h"

Board::Board(int width, int height, char live, char dead, char wall) {
	this->width = width;
	this->height = height;

	livechar = live;
	deadchar = dead;
	wallchar = wall;

	std::vector<bool> row;
	row.resize(width, false);

	this->cells.resize(height, row);
	// On désalloue row
	row.clear();
}

Board::~Board() {
	this->cells.clear();
}

void Board::dim(int &w, int &h) const {
	w = this->width;
	h = this->height;
}

bool Board::operator()(int i, int j) const {
	return this->cells[j][i];
}

int Board::neighbors(int i, int j) const {
	int res = 0;
	int h = this->height - 1;
	int w = this->width - 1;
	if(i > 0 && j > 0 && (*this)(i - 1, j - 1)) res += 1;
	if(         j > 0 && (*this)(i,     j - 1)) res += 1;
	if(i < w && j > 0 && (*this)(i + 1, j - 1)) res += 1;
	if(i > 0 &&          (*this)(i - 1, j    )) res += 1;
	if(i < w &&          (*this)(i + 1, j    )) res += 1;
	if(i > 0 && j < h && (*this)(i - 1, j + 1)) res += 1;
	if(         j < h && (*this)(i,     j + 1)) res += 1;
	if(i < w && j < h && (*this)(i + 1, j + 1)) res += 1;
	return res;
}

void Board::toggle(int i, int j) {
	this->cells[j][i] = !(*this)(i, j);
}

bool Board::nextstate(int i, int j) {
	int n = neighbors(i, j);
	int born(3), surv(2);
	//bool res = this->cells[j][i];
	//if(n < 2)
	//	res = false;
	//else if(n >= 3)
	//	res = n == 3;
	//return res;
	return (n == born) || (n == surv && this->cells[j][i]);
	//return (n > 1 && n < 4) || this->cells[j][i];
}

void Board::nextgen() {
	std::vector<bool> row;
	row.resize(this->width, false);
	std::vector<std::vector<bool>> next;
	next.resize(this->height, row);

	for(int i = 0; i < this->width; ++i) {
		for(int j = 0; j < this->height; ++j) {
			next[j][i] = this->nextstate(i, j);
		}
	}
	this->cells = next;
}

std::ostream& operator<<(std::ostream& out, const Board& b) {
	for(int j(0); j < b.height; ++j) {
		for(int i(0); i < b.width; ++i)
			out << (b.cells[j][i] ? b.livechar : b.deadchar);
		out << std::endl;
	}
	return out;
}

std::string Board::tostring() const {
	std::string res(wallchar, width);
	for(int j(0); j < height; ++j) {
		res += wallchar;
		for(int i(0); i < width; ++i)
			res += (cells[j][i] ? livechar : deadchar);
		res += wallchar;
		res += '\n';
	}
	std::cerr << res;
	return res;
}
