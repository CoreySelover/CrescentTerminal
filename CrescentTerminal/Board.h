#pragma once

// STD
#include <vector>

// SFML
#include <SFML/Graphics.hpp>

// Crescent Terminal
#include "Tile.h"
class Building;
enum BuildingType;

class Board {
public:
    Board(int width, int height, TileType defaultTile = TileType_Dirt);

    // Tiles
    Tile& getTile(int x, int y);
    Tile& getTile(sf::Vector2i tilePosition);
    bool isTileObstacle(int x, int y) const;
    bool isTileInBounds(int x, int y) const;
    bool isTileOnScreen(int x, int y, sf::RenderWindow& window) const;
    void highlightTiles(sf::Vector2i footprint, sf::Vector2f mousePos, bool canBuild);
    void clearHighlights();

    // Buildings
    void buildBuilding(BuildingType type, sf::Vector2f position);

    // Drawing
    void drawBackground(sf::RenderWindow& window);
    void drawForeground(sf::RenderWindow& window) const {
        // TODO
    }

    // Helpers
    sf::Vector2f getBoardSize() const;
    static sf::Vector2i pixelsToTileCoords(sf::Vector2f pixelPosition);
    static sf::Vector2f tileCoordsToPixels(sf::Vector2i tilePosition);

private:
    int m_width;
    int m_height;
    std::vector<std::vector<Tile>> m_tiles;
    std::vector<std::shared_ptr<Building>> m_buildings;
};


