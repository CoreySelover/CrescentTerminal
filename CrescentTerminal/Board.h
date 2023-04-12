#pragma once

// STD
#include <vector>

// SFML
#include <SFML/Graphics.hpp>

// Crescent Terminal
#include "Tile.h"

class Board {
public:
    Board(int width, int height, TileType defaultTile = TileType_Dirt);

    Tile& getTile(int x, int y);

    Tile& getTile(sf::Vector2i tilePosition);

    bool isTileObstacle(int x, int y) const;

    bool isTileInBounds(int x, int y) const;

    bool isTileOnScreen(int x, int y, sf::RenderWindow& window) const;

    void drawBackground(sf::RenderWindow& window);

    void drawForeground(sf::RenderWindow& window) const {
        // TODO
    }

    static sf::Vector2i pixelsToTileCoords(sf::Vector2f pixelPosition);

    static sf::Vector2f tileCoordsToPixels(sf::Vector2i tilePosition);

private:
    int m_width;
    int m_height;
    std::vector<std::vector<Tile>> m_tiles;
};


