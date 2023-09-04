#include "Player.h"

Player::Player(const std::string& s, Token t) : name(s), token(t) {}

const std::string& Player::getName() const {
	return name;
}

const Token Player::getTokenColour() const {
	return token;
}