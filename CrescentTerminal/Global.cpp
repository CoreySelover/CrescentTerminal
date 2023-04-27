#include "Global.h"

#include <string>
#include <sstream>

// Meta
sf::Clock GAME_CLOCK;

// Helper function to split a string into a vector of strings based on a delimiter
std::vector<std::string> splitString(const std::string& s, char delimiter) {
	std::vector<std::string> tokens;
	std::string token;
	std::istringstream tokenStream(s);
	while (std::getline(tokenStream, token, delimiter)) {
		tokens.push_back(token);
	}
	return tokens;
}

// UI
bool USER_HAS_CONTROL = true;
bool DEBUG_DRAW = false;

// Board
const int TILE_SIZE = 32;
const std::vector<std::string> LAYER_NAMES = { "Background", "Obstacles", "Foreground", "Doors"};

// Characters
const float WALK_SPEED = 0.1f;

std::string directionToString(Direction direction) {
	switch (direction) {
	case UP:
		return "up";
	case DOWN:
		return "down";
	case LEFT:
		return "left";
	case RIGHT:
		return "right";
	default:
		return "UNKNOWN";
	}
}
