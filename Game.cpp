#include "Game.h"
#include "Token.h"
#include <iostream>
#include <algorithm>

Game::Game(Grid& g, int n, int target) : grid(g), connectN(n), targetScore(target) {
	players.insert(new Player("Player 1", Token::RED));
	players.insert(new Player("Player 2", Token::YELLOW));
	/*players = std::set<Player*>{
			new Player("Player 1", Token::RED),
			new Player("Player 2", Token::YELLOW)
	};
	scoreTable = std::map<std::string, int>();*/
	for (Player* p : players)
		scoreTable[p->getName()] = 0;
}

Game::~Game() {
	for (Player* p : players)
		delete p;
}

void Game::printBoard() const {
	std::cout << "Current Board:" << std::endl << std::endl;
	std::vector<std::vector<Token>>& board = grid.getGrid();
	for (int i = 0; i < board.size(); ++i) {
		std::string row;
		for (Token t : board[i]) {
			if (t == Token::EMPTY)
				row += "O ";
			else if (t == Token::RED)
				row += "X ";
			else // possible control flow error
				row += "@ ";
		}
		std::cout << row << std::endl;
	}
	std::cout << std::endl;
	std::string colIndx;
	for (int i = 0; i < grid.getColumnCount(); ++i)
		colIndx += std::to_string(i) + " ";
	std::cout << colIndx << std::endl << std::endl;
}

std::pair<int, int> Game::playMove(Player* player) {
	printBoard();
	std::cout << player->getName() << "'s turn" << std::endl;
	int colCount = grid.getColumnCount();
	std::cout << "Enter a column number between 0 and " << (colCount - 1) 
		<< " to add a token: ";
	int moveCol = 0; // keep track of the column the token is placed in
	std::cin >> moveCol;
	std::cout << std::endl;
	std::vector<std::vector<Token>>& board = grid.getGrid();
	if (board[0][moveCol] != Token::EMPTY)
		throw "Non-empty Column";
	// Place a token and keep track of the row the token is placed in
	int moveRow = grid.placeToken(moveCol, player->getTokenColour());
	return { moveRow, moveCol };
}

Player* Game::playRound() {
	int moves = 0;
	while (1) {
		for (Player* p : players) {
			std::pair<int, int> pos = playMove(p);
			++moves;
			if (moves == grid.maxTokens())
				return nullptr;
			int row = pos.first;
			int col = pos.second;
			Token t = p->getTokenColour();
			if (grid.checkNConnected(connectN, row, col, t)) {
				++scoreTable[p->getName()];
				return p;
			}
		}
	}
	return nullptr;
}

void Game::playGame() {
	int maxScore = 0;
	Player* winner = *(players.begin());
	while (maxScore < targetScore) {
		winner = playRound();
		if (!winner)
			std::cout << "The round ended in a tie" << std::endl << std::endl;
		else {
			std::cout << winner->getName() << " won the round" << std::endl << std::endl;
			maxScore = std::max(scoreTable[winner->getName()], maxScore);
		}
		grid.initGrid();
	}
	std::cout << winner->getName() << " won the game" << std::endl;
}

void playConnect4(int targetScore) {
	Grid grid(6, 7);
	Game newGame(grid, 4, targetScore);
	newGame.playGame();
}
