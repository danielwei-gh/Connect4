#ifndef GAME_H
#define GAME_H

#include "Grid.h"
#include "Player.h"
#include <map>
#include <set>

class Game {
public:
	Game(Grid&, int, int);
	~Game();
	void printBoard() const;
	void playGame();
private:
	Grid& grid;
	int connectN;
	std::set<Player*> players;
	std::map<std::string, int> scoreTable;
	int targetScore;
	std::pair<int, int> playMove(Player*);
	Player* playRound();
};

void playConnect4(int);

#endif
