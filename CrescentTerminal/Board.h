#pragma once

// STD
#include <vector>
#include <iostream>

// SFML
#include <SFML/Graphics.hpp>

// Crescent Terminal
#include "Tile.h"
#include "Global.h"

class Board {
public:
    Board(int width, int height, TileType defaultTile = TileType_Dirt)
        : m_width(width)
        , m_height(height)
        , m_tiles(width, std::vector<Tile>(height))
    {
        for (int x = 0; x < m_width; ++x) {
            for (int y = 0; y < m_height; ++y) {
                m_tiles[x][y].setType(defaultTile);
            }
        }
    }

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

    bool isTileOnScreen(int x, int y, sf::RenderWindow& window) const {
        sf::Vector2f viewCenter = window.getView().getCenter();
        sf::Vector2f viewSize = window.getView().getSize();
        sf::Vector2f position = tileCoordsToPixels({ x, y });
        if (position.x < 0 || 
            position.x < viewCenter.x - viewSize.x / 2 - TILE_SIZE ||
            position.x > viewCenter.x + viewSize.x / 2 || 
            position.y < 0 || 
            position.y < viewCenter.y - viewSize.y / 2 - TILE_SIZE ||
            position.y > viewCenter.y + viewSize.y / 2)
        {
            return false;
        }
        return true;
    }

    void drawBackground(sf::RenderWindow& window) {
        for (int x = 0; x < m_width; ++x) {
            for (int y = 0; y < m_height; ++y) {
                if (isTileOnScreen(x, y, window)) {
                    m_tiles[x][y].draw(window, { float(x * TILE_SIZE), float(y * TILE_SIZE) });
                }  
            }
        }
    }

    void drawForeground(sf::RenderWindow& window) const {
        // TODO
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

