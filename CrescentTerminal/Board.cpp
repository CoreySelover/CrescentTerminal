#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "pugixml.hpp"

#include "Board.h"
#include "Global.h"
#include "Building.h"

Board::Board(std::string name, int width, int height, BoardType type, TileType defaultTile)
    : m_name(name)
    , m_width(width)
    , m_height(height)
    , m_type(type)
{
    resizeVectors();

    for (int x = 0; x < m_width; ++x) {
        for (int y = 0; y < m_height; ++y) {
            m_drawLayers["Background"].m_tiles[x][y].setType(defaultTile);
            m_drawLayers["Background"].m_tiles[x][y].setTextureRect(sf::IntRect(0, 0, TILE_SIZE, TILE_SIZE));
        }
    }

    if (m_name == "World") {
		loadLevel("Assets/Maps/test.xml");
	}
}

Board::~Board()
{
    m_doors.clear();

    // Loop through layers and clear tiles
    for (auto& layer : m_drawLayers) {
		layer.second.m_tiles.clear();
	}
    m_drawLayers.clear();
}

void Board::resizeVectors()
{
    m_drawLayers["Background"].m_tiles.resize(m_width);
    for (int x = 0; x < m_width; ++x) {
        m_drawLayers["Background"].m_tiles[x].resize(m_height);
    }

    m_drawLayers["Obstacles"].m_tiles.resize(m_width);
    for (int x = 0; x < m_width; ++x) {
        m_drawLayers["Obstacles"].m_tiles[x].resize(m_height);
    }

    m_drawLayers["Foreground"].m_tiles.resize(m_width);
    for (int x = 0; x < m_width; ++x) {
        m_drawLayers["Foreground"].m_tiles[x].resize(m_height);
    }

    m_doors.resize(m_width);
    for (int x = 0; x < m_width; ++x) {
		m_doors[x].resize(m_height);
	}
}

void Board::clearBuildings()
{
	m_buildings.clear();
}

void Board::loadLevel(std::string filename)
{
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(filename.c_str());

    if (!result) {
		std::cout << "Error loading level: " << filename << std::endl;
		return;
	}

    pugi::xml_node map = doc.child("map");
	m_width = map.attribute("width").as_int();
	m_height = map.attribute("height").as_int();

    resizeVectors();

	// Load tiles
    for (pugi::xml_node layer = map.child("layer"); layer; layer = layer.next_sibling("layer"))
    {
        std::string layerName = layer.attribute("name").as_string();

        // Get the CSV-encoded tile data from the "data" element
        std::string csvData = layer.child("data").text().get();

        // Split the CSV data into individual tile IDs
        std::vector<std::string> tileIds = splitString(std::string(csvData).c_str(), ',');

        // Load tile data
        int x = 0;
        int y = 0;
        // Our tileset texture is 10 tiles wide
        const int textureWidth = 10;
        for (const std::string& tileId : tileIds) {
            int id = std::stoi(tileId);
            // Empty tiles
            if (id == 0) {
				m_drawLayers[layerName].m_tiles[x][y].setType(TileType_Empty);
			}
            // Obstacles
            else if (layerName == "Obstacles") {
                std::cout << "Obstacle at " << x << ", " << y << std::endl;
                m_drawLayers["Obstacles"].m_tiles[x][y].setObstacle(true);
                m_drawLayers["Obstacles"].m_tiles[x][y].setType(TileType_Wall);
            }

            // Texture rects
            int tileIndex = id - 1; // adjust index to start at 0
            int tileX = tileIndex % textureWidth;
            int tileY = tileIndex / textureWidth;
            sf::IntRect textureRect(tileX * TILE_SIZE, tileY * TILE_SIZE, TILE_SIZE, TILE_SIZE);
            m_drawLayers[layerName].m_tiles[x][y].setTextureRect(textureRect);

            // Next column and/or row
            x++;
            if (x == map.attribute("width").as_int()) {
                x = 0;
                y++;
            }
        }
    }
}

// Helper function to split a string into a vector of strings based on a delimiter
std::vector<std::string> Board::splitString(const std::string& s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

Tile& Board::getTile(int x, int y, std::string layer)
{
	return m_drawLayers[layer].m_tiles[x][y];
}

Tile& Board::getTile(sf::Vector2i tilePosition, std::string layer)
{
	return m_drawLayers[layer].m_tiles[tilePosition.x][tilePosition.y];
}

bool Board::isTileObstacle(int x, int y)
{
    return m_drawLayers["Obstacles"].m_tiles[x][y].isObstacle();
}

bool Board::isTileInBounds(int x, int y)
{
	return x >= 0 && x < m_width && y >= 0 && y < m_height;
}

bool Board::isTileOnScreen(int x, int y, sf::RenderWindow& window) const
{
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

bool Board::isTileBuildEligible(int x, int y, std::string layer)
{
    return m_drawLayers[layer].m_tiles[x][y].isBuildEligible();
}

void Board::highlightTiles(sf::Vector2i footprint, sf::Vector2f mousePos, bool canBuild)
{
    // Reset all tiles
    for (int x = 0; x < m_width; ++x) {
        for (int y = 0; y < m_height; ++y) {
            m_drawLayers["Foreground"].m_tiles[x][y].setHighlight(sf::Color::Transparent);
		}
	}

    // Highlight new tiles
	sf::Vector2i tileCoords = pixelsToTileCoords(mousePos);
    for (int x = 0; x < footprint.x; ++x) {
        for (int y = 0; y < footprint.y; ++y) {
            if (isTileInBounds(tileCoords.x + x, tileCoords.y + y)) {
                if (canBuild) {
                    m_drawLayers["Foreground"].m_tiles[tileCoords.x + x][tileCoords.y + y].setHighlight(sf::Color::Green);
                }
                else {
                    m_drawLayers["Foreground"].m_tiles[tileCoords.x + x][tileCoords.y + y].setHighlight(sf::Color::Red);
                }
            }
		}
	}
}

void Board::clearHighlights()
{
    for (int x = 0; x < m_width; ++x) {
        for (int y = 0; y < m_height; ++y) {
            m_drawLayers["Foreground"].m_tiles[x][y].setHighlight(sf::Color::Transparent);
		}
	}
}

void Board::drawBackground(sf::RenderWindow& window)
{
    for (int x = 0; x < m_width; ++x) {
        for (int y = 0; y < m_height; ++y) {
            if (isTileOnScreen(x, y, window)) {
                m_drawLayers["Background"].m_tiles[x][y].draw(window, {float(x * TILE_SIZE), float(y * TILE_SIZE)});
            }
        }
    }
}

void Board::drawObstacles(sf::RenderWindow& window)
{
    for (int x = 0; x < m_width; ++x) {
        for (int y = 0; y < m_height; ++y) {
            if (isTileOnScreen(x, y, window)) {
                m_drawLayers["Obstacles"].m_tiles[x][y].draw(window, { float(x * TILE_SIZE), float(y * TILE_SIZE) });
            }
        }
    }
}

void Board::drawForeground(sf::RenderWindow& window)
{
    for (int x = 0; x < m_width; ++x) {
        for (int y = 0; y < m_height; ++y) {
            if (isTileOnScreen(x, y, window)) {
                m_drawLayers["Foreground"].m_tiles[x][y].draw(window, { float(x * TILE_SIZE), float(y * TILE_SIZE) });
            }
        }
    }
}

void Board::buildBuilding(BuildingType type, sf::Vector2f position) {
    sf::Vector2i tileCoords = pixelsToTileCoords(position);
	m_buildings.push_back(std::make_shared<Building>(type, m_name, tileCoords, true));
    std::shared_ptr<Building> newBuilding = m_buildings.back();

    // Update tiles to reflect new building
    for (int x = 0; x < newBuilding->getFootprintSize().x; ++x) {
        for (int y = 0; y < newBuilding->getFootprintSize().y; ++y) {
            m_drawLayers["Background"].m_tiles[tileCoords.x + x][tileCoords.y + y].setType(newBuilding->getTileType(sf::Vector2i(x, y)));
            // Add a door if the tile is a door
            if (newBuilding->getTileType(sf::Vector2i(x, y)) == TileType_Door) {
                m_doors[tileCoords.x + x][tileCoords.y + y] = Door({ newBuilding->getInterior()->getName(), sf::Vector2i(2,2) });
			}
		}
	}
}

bool Board::canBuildHere(sf::Vector2i footprint, sf::Vector2f mousepos, int buffer) {
    sf::Vector2i tileCoords = pixelsToTileCoords(mousepos);
    for (int x = -buffer; x < footprint.x + buffer; ++x) {
        for (int y = -buffer; y < footprint.y + buffer; ++y) {
            if (!isTileInBounds(tileCoords.x + x, tileCoords.y + y)) {
				return false;
			}
            if (isTileObstacle(tileCoords.x + x, tileCoords.y + y)) {
				return false;
			}
            if (!isTileBuildEligible(tileCoords.x + x, tileCoords.y + y)) {
				return false;
            }
		}
	}
	return true;
}

void Board::addDoor(sf::Vector2i position, std::string destinationName, sf::Vector2i destinationPosition)
{
	m_doors[position.x][position.y] = Door({ destinationName, destinationPosition });
}

std::string Board::getDoorDestinationName(sf::Vector2i position) const
{
    if (m_doors[position.x][position.y].destinationName != "") {
		return m_doors[position.x][position.y].destinationName;
    }
    return "NOT_FOUND";
}

sf::Vector2i Board::getDoorDestinationStartPos(sf::Vector2i position) const
{
    if (m_doors[position.x][position.y].destinationName != "") {
		return m_doors[position.x][position.y].destinationPosition;
	}
	return sf::Vector2i(-1, -1);
}

sf::Vector2f Board::getBoardSize() const
{
	return sf::Vector2f(float(m_width * TILE_SIZE), float(m_height * TILE_SIZE));
}

sf::Vector2i Board::pixelsToTileCoords(sf::Vector2f pixelPosition)
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

sf::Vector2f Board::tileCoordsToPixels(sf::Vector2i tilePosition)
{
	return sf::Vector2f(float(tilePosition.x * TILE_SIZE), float(tilePosition.y * TILE_SIZE));
}

