#include "Grid.h"

Grid::Grid(int r, int c) : rows(r), columns(c) {
	initGrid();
}

// Grid Initiallization: Adding empty rows to the grid
void Grid::initGrid() {
	grid = std::vector<std::vector<Token>>();
	for (int i = 0; i < rows; ++i) {
		grid.push_back(std::vector<Token>());
		for (int j = 0; j < columns; ++j)
			grid[i].push_back(Token::EMPTY);
	}
}

std::vector<std::vector<Token>>& Grid::getGrid() {
	return grid;
}

int Grid::getColumnCount() const {
	return columns;
}

// Placing the token in the lowest empty row
int Grid::placeToken(int col, Token t) {
	if (col < 0 || col >= columns)
		throw "Invalid column";
	if (t == Token::EMPTY)
		throw "Invalid piece";
	for (int row = rows - 1; row >= 0; --row) {
		if (grid[row][col] == Token::EMPTY) {
			grid[row][col] = t;
			return row;
		}
	}
	return -1;
}

// Checking if n tokens are connected after a token has been placed
bool Grid::checkNConnected(int n, int row, int col, Token t) const {
	// check horizontal
	int count = 0;
	for (int c = 0; c < columns; ++c) {
		if (grid[row][c] == t)
			++count;
		else
			count = 0;
		if (count == n)
			return true;
	}
	// check vertical
	count = 0;
	for (int r = 0; r < rows; ++r) {
		if (grid[r][col] == t)
			++count;
		else
			count = 0;
		if (count == n)
			return true;
	}
	// check positive diagonal
	count = 0;
	for (int r = 0; r < rows; ++r) {
		int c = row + col - r; // row + col = r + c for positive diagonal coordinates
		if (c >= 0 && c < columns && grid[r][c] == t)
			++count;
		else
			count = 0;
		if (count == n)
			return true;
	}
	// check negative diagonal
	count = 0;
	for (int c = 0; c < columns; ++c) {
		int r = row - col + c; // row - col = r - c for negative diagonal coordinates
		if (r >= 0 && r < rows && grid[r][c] == t)
			++count;
		else
			count = 0;
		if (count == n)
			return true;
	}
	return false;
}

int Grid::maxTokens() const {
	return rows * columns;
}