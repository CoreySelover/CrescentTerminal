#pragma once

#include <string>

// UI
extern bool USER_HAS_CONTROL;
extern bool DEBUG_DRAW;

// Board
extern const int TILE_SIZE;

// Characters
extern const float WALK_SPEED;
enum Direction { UP, DOWN, LEFT, RIGHT };
std::string directionToString(Direction direction);


