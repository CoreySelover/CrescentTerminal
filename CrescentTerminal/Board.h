#pragma once

// STD
#include <vector>

// SFML
#include <SFML/Graphics.hpp>

// Crescent Terminal
#include "Tile.h"

struct Door {
    std::string destinationName;
    sf::Vector2i destinationPosition;
};

struct DrawLayer {
    std::string m_name;
    std::vector<std::vector<Tile>> m_tiles;
};

class Building;
enum BuildingType;

class Board {
public:
    Board(std::string name, std::string filePath);
    ~Board();
    void resizeVectors();
    void clearBuildings();
    void loadLevel(std::string filename);

    // Tiles
    Tile& getTile(int x, int y, std::string layer = "Background");
    Tile& getTile(sf::Vector2i tilePosition, std::string layer = "Background");

    bool isTileObstacle(int x, int y);
    bool isTileInBounds(int x, int y);
    bool isTileOnScreen(int x, int y, sf::RenderWindow& window) const;
    bool isTileBuildEligible(int x, int y, std::string layer = "Background");

    void highlightTiles(sf::Vector2i footprint, sf::Vector2f mousePos, bool canBuild);
    void clearHighlights();

    // Buildings
    void buildBuilding(BuildingType type, sf::Vector2f position);
    bool canBuildHere(sf::Vector2i footprint, sf::Vector2f mousepos, int buffer = 0);
    std::shared_ptr<Building> lastBuilding() const { return m_buildings.back(); }

    // Doors
    void addDoor(sf::Vector2i position, std::string destinationName, sf::Vector2i destinationPosition);
    bool isDoor(sf::Vector2i position) const;
    std::string getDoorDestinationName(sf::Vector2i position) const;
    sf::Vector2i getDoorDestinationStartPos(sf::Vector2i position) const;

    // Drawing
    void drawBackground(sf::RenderWindow& window);
    void drawObstacles(sf::RenderWindow& window);
    void drawForeground(sf::RenderWindow& window);

    // Helpers
    sf::Vector2f getBoardSize() const;
    std::string getName() const { return m_name; }

private:
    std::string m_name;
    int m_width;
    int m_height;
    std::vector<std::shared_ptr<Building>> m_buildings;
    std::vector<std::vector<Door>> m_doors;
    std::map<std::string, DrawLayer> m_drawLayers;
};


