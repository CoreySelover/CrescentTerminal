#pragma once

#include <string>

#include <SFML/Graphics.hpp>

// Meta
extern sf::Clock GAME_CLOCK;
std::vector<std::string> splitString(const std::string& s, char delimiter);


// UI
extern bool USER_HAS_CONTROL;
extern bool DEBUG_DRAW;

// Board
extern const int TILE_SIZE;
extern const std::vector<std::string> LAYER_NAMES;

// Characters
extern const float WALK_SPEED;
enum Direction { UP, DOWN, LEFT, RIGHT };
std::string directionToString(Direction direction);


