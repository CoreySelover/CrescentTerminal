#pragma once

// STD
#include <vector>

// SFML
#include <SFML/Graphics.hpp>

// Crescent Terminal
#include "Tile.h"

enum BoardType {
	BoardType_World,
	BoardType_Interior,
	BoardType_Count
};

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
    Board(std::string name, int width, int height, BoardType type = BoardType_World, TileType defaultTile = TileType_Floor);
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
    std::string getDoorDestinationName(sf::Vector2i position) const;
    sf::Vector2i getDoorDestinationStartPos(sf::Vector2i position) const;

    // Drawing
    void drawBackground(sf::RenderWindow& window);
    void drawObstacles(sf::RenderWindow& window);
    void drawForeground(sf::RenderWindow& window);

    // Helpers
    sf::Vector2f getBoardSize() const;
    std::string getName() const { return m_name; }
    static sf::Vector2i pixelsToTileCoords(sf::Vector2f pixelPosition);
    static sf::Vector2f tileCoordsToPixels(sf::Vector2i tilePosition);

private:
    std::string m_name;
    int m_width;
    int m_height;
    BoardType m_type;
    std::vector<std::shared_ptr<Building>> m_buildings;
    std::vector<std::vector<Door>> m_doors;
    std::map<std::string, DrawLayer> m_drawLayers;

    std::vector<std::string> splitString(const std::string& s, char delimiter);
};


