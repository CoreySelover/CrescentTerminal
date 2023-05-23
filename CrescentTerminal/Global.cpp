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
sf::Vector2u RESOLUTION = sf::Vector2u(0, 0);

// Board
const int TILE_SIZE = 32;
const std::vector<std::string> LAYER_NAMES = { "Background", "Shadows", "Obstacles", "Foreground", "Doors"};

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

sf::Vector2i pixelsToTileCoords(sf::Vector2f pixelPosition)
{
	// Because e.g. int(-5 / 32) = 0, but we want it to resolve to -1
	if (pixelPosition.x < 0) {
		pixelPosition.x -= TILE_SIZE;
	}
	if (pixelPosition.y < 0) {
		pixelPosition.y -= TILE_SIZE;
	}

	sf::Vector2i tileCoords;
	tileCoords.x = int(pixelPosition.x / TILE_SIZE);
	tileCoords.y = int(pixelPosition.y / TILE_SIZE);

	return tileCoords;
}

sf::Vector2i pixelsToTileCoords(float x, float y)
{
	return pixelsToTileCoords(sf::Vector2f(x, y));
}

sf::Vector2f tileCoordsToPixels(sf::Vector2i tilePosition)
{
	return sf::Vector2f(float(tilePosition.x * TILE_SIZE), float(tilePosition.y * TILE_SIZE));
}

sf::Vector2f tileCoordsToPixels(int x, int y)
{
	return tileCoordsToPixels(sf::Vector2i(x, y));
}