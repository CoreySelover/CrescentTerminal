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
struct TimeDate;

class Board {
public:
    Board(std::string name, std::string filePath, bool interior);
    ~Board();
    void resizeVectors();
    void clearBuildings();
    void loadFromFile(std::string filename);
    void update(TimeDate& timeDate, sf::RenderWindow& window);
    bool isInterior() const { return m_isInterior; }
    void drawDarkness(sf::RenderWindow& window);

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
    void drawShadows(sf::RenderWindow& window);
    void drawObstacles(sf::RenderWindow& window);
    void drawForeground(sf::RenderWindow& window);

    // Helpers
    sf::Vector2f getBoardSizeInPixels() const;
    sf::Vector2i getBoardSizeInCoords() const;
    std::string getName() const { return m_name; }
    std::string getFileName() const { return m_fileName; }
    std::map<std::string, sf::Vector2i> getEntrances() const { return m_entrances; }
    std::vector<std::shared_ptr<Building>> getBuildings() const { return m_buildings; }

private:
    std::string m_name;
    int m_width;
    int m_height;
    std::string m_fileName;
    bool m_isInterior;

    std::vector<std::shared_ptr<Building>> m_buildings;
    std::vector<std::vector<Door>> m_doors;
    std::map<std::string, sf::Vector2i> m_entrances;
    std::map<std::string, DrawLayer> m_drawLayers;

    sf::RectangleShape m_darkness;
};


