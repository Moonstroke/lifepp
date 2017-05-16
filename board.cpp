#include "board.h"

Board::Board(int width, int height, char livechar, char deadchar, char wallchar) : w(width), h(height), live(livechar), dead(deadchar), wall(wallchar) {
	// this->w = width;
	// this->h = height;
	//
	// live = livechar;
	// dead = deadchar;
	// wall = wallchar;

	std::vector<bool> row;
	row.resize(width, false);

	cells.resize(height, row);
	// On désalloue row
	row.clear();
}

Board::~Board() {
	cells.clear();
}

void Board::dim(int &width, int &height) const {
	width = w;
	height = h;
}

bool Board::operator()(int i, int j) const {
	return cells[j][i];
}

int Board::neighbors(int i, int j) const {
	int res = 0;
	int h = this->h - 1;
	int w = this->w - 1;
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
	cells[j][i] = !(*this)(i, j);
}

bool Board::nextstate(int i, int j) const {
	int n = neighbors(i, j);
	int born(3), surv(2);
	//bool res = this->cells[j][i];
	//if(n < 2)
	//	res = false;
	//else if(n >= 3)
	//	res = n == 3;
	//return res;
	return (n == born) || (n == surv && cells[j][i]);
	//return (n > 1 && n < 4) || this->cells[j][i];
}

void Board::nextgen() {
	std::vector<bool> row;
	row.resize(this->w, false);
	std::vector<std::vector<bool>> next;
	next.resize(this->h, row);

	for(int i = 0; i < this->w; ++i) {
		for(int j = 0; j < this->h; ++j) {
			next[j][i] = nextstate(i, j);
		}
	}
	this->cells = next;
}

std::ostream& operator<<(std::ostream& out, const Board& b) {
	for(int j(0); j < b.h; ++j) {
		for(int i(0); i < b.w; ++i)
			out << (b.cells[j][i] ? b.live : b.dead);
		out << std::endl;
	}
	return out;
}

std::string Board::tostring() const {
	std::string res;
	// std::string res(width + 2, wallchar);
	// res += '\n';
	for(int j(0); j < h; ++j) {
		// res += wallchar;
		for(int i(0); i < w; ++i)
			res += (cells[j][i] ? live : dead);
		// res += wallchar;
		res += '\n';
	}
	// res += std::string(width + 2, wallchar);
	std::cerr << res;
	return res;
}
