#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "Token.h"

class Player {
public:
	Player(const std::string&, Token);
	const std::string& getName() const;
	const Token getTokenColour() const;
private:
	std::string name;
	Token token;
};

#endif