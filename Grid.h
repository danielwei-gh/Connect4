#ifndef GRID_H
#define GRID_H

#include <vector>
#include "Token.h"

class Grid {
public:
	Grid(int, int);
	void initGrid();
	std::vector<std::vector<Token>>& getGrid();
	int getColumnCount() const;
	int placeToken(int, Token);
	bool checkNConnected(int, int, int, Token) const;
	int maxTokens() const;
private:
	int rows;
	int columns;
	std::vector<std::vector<Token>> grid;
};

#endif