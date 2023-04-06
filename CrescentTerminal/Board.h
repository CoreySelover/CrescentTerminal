#pragma once

// STD
#include <vector>

// SFML
#include <SFML/Graphics.hpp>

// Crescent Terminal
#include "Tile.h"

class Board {
public:
    Board(int width, int height, int tileSize)
        : m_width(width)
        , m_height(height)
        , m_tileSize(tileSize)
        , m_tiles(width, std::vector<Tile>(height))
    {}

    Tile& getTile(int x, int y) {
        return m_tiles[x][y];
    }

    void draw(sf::RenderWindow& window) const {
        for (int x = 0; x < m_width; ++x) {
            for (int y = 0; y < m_height; ++y) {
                m_tiles[x][y].draw(window, { float(x * m_tileSize), float(y * m_tileSize) }, { float(m_tileSize), float(m_tileSize) });
            }
        }
    }

private:
    int m_width;
    int m_height;
    int m_tileSize;
    std::vector<std::vector<Tile>> m_tiles;
};


