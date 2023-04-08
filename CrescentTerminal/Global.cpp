#include "Global.h"

#include <string>

// UI
bool USER_HAS_CONTROL = true;
bool DEBUG_DRAW = false;

// Board
const int TILE_SIZE = 32;

// Characters
const float WALK_SPEED = 0.2f;

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
