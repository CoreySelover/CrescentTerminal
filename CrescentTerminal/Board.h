#pragma once

// STD
#include <vector>

// SFML
#include <SFML/Graphics.hpp>

// Crescent Terminal
#include "Tile.h"
#include "Global.h"

class Board {
public:
    Board(int width, int height)
        : m_width(width)
        , m_height(height)
        , m_tiles(width, std::vector<Tile>(height))
    {}

    Tile& getTile(int x, int y) {
        return m_tiles[x][y];
    }

    Tile& getTile(sf::Vector2i tilePosition) {
		return m_tiles[tilePosition.x][tilePosition.y];
	}

    bool isTileObstacle(int x, int y) const {
		return m_tiles[x][y].isObstacle();
	}

    bool isTileInBounds(int x, int y) const {
		return x >= 0 && x < m_width && y >= 0 && y < m_height;
	}

    void draw(sf::RenderWindow& window) const {
        for (int x = 0; x < m_width; ++x) {
            for (int y = 0; y < m_height; ++y) {
                m_tiles[x][y].draw(window, { float(x * TILE_SIZE), float(y * TILE_SIZE) }, { float(TILE_SIZE), float(TILE_SIZE) });
            }
        }
    }

    static sf::Vector2i pixelsToTileCoords(sf::Vector2f pixelPosition) {
        return sf::Vector2i(int(pixelPosition.x / TILE_SIZE), int(pixelPosition.y / TILE_SIZE));
    }

    static sf::Vector2f tileCoordsToPixels(sf::Vector2i tilePosition) {
		return sf::Vector2f(float(tilePosition.x * TILE_SIZE), float(tilePosition.y * TILE_SIZE));
	}

private:
    int m_width;
    int m_height;
    std::vector<std::vector<Tile>> m_tiles;
};


