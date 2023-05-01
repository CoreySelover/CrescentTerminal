#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "pugixml.hpp"

#include "Board.h"
#include "Global.h"
#include "Building.h"

Board::Board(std::string name, std::string filePath)
    : m_name(name)
{
    m_width = -1;
    m_height = -1;
    loadLevel(filePath);
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
    for (auto& layer : m_drawLayers) {
        layer.second.m_tiles.resize(m_width);
        for (int x = 0; x < m_width; ++x) {
			layer.second.m_tiles[x].resize(m_height);
		}
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

    for (auto lName : LAYER_NAMES) {
        m_drawLayers[lName] = DrawLayer{ lName, std::vector<std::vector<Tile>>(m_width, std::vector<Tile>(m_height))
        };
    }

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
                m_drawLayers["Obstacles"].m_tiles[x][y].setObstacle(true);
                m_drawLayers["Obstacles"].m_tiles[x][y].setType(TileType_Wall);
            }
            // Doors
            else if (layerName == "Doors") {
                m_drawLayers["Background"].m_tiles[x][y].setType(TileType_Door);
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
            m_drawLayers["Background"].m_tiles[x][y].setHighlight(sf::Color::Transparent);
		}
	}

    // Highlight new tiles
	sf::Vector2i tileCoords = pixelsToTileCoords(mousePos);
    for (int x = 0; x < footprint.x; ++x) {
        for (int y = 0; y < footprint.y; ++y) {
            if (isTileInBounds(tileCoords.x + x, tileCoords.y + y)) {
                if (canBuild) {
                    m_drawLayers["Background"].m_tiles[tileCoords.x + x][tileCoords.y + y].setHighlight(sf::Color::Green);
                }
                else {
                    m_drawLayers["Background"].m_tiles[tileCoords.x + x][tileCoords.y + y].setHighlight(sf::Color::Red);
                }
            }
		}
	}
}

void Board::clearHighlights()
{
    for (int x = 0; x < m_width; ++x) {
        for (int y = 0; y < m_height; ++y) {
            m_drawLayers["Background"].m_tiles[x][y].setHighlight(sf::Color::Transparent);
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

    // Update tiles on all drawLayers to reflect new building
    for (int x = 0; x < newBuilding->getFootprintSize().x; ++x) {
        for (int y = 0; y < newBuilding->getFootprintSize().y; ++y) {
            for (auto& layer : m_drawLayers) {
				std::string layerName = layer.first;
                m_drawLayers[layerName].m_tiles[tileCoords.x + x][tileCoords.y + y] = newBuilding->getTile(layerName, sf::Vector2i(x, y));
            }

            // Add a door if the tile is a door
            if (newBuilding->getTile("Doors", sf::Vector2i(x, y)).getType() != TileType_Empty) 
            {
                sf::Vector2i entrance = newBuilding->getInterior()->getBoardSizeInCoords();
                entrance.x = (entrance.x - 1) / 2;
                entrance.y -= 2;
                m_doors[tileCoords.x + x][tileCoords.y + y] = Door({ newBuilding->getInterior()->getName(), entrance });
                
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

bool Board::isDoor(sf::Vector2i position) const
{
    if (m_doors[position.x][position.y].destinationName != "") {
		return true;
	}
	return false;
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

sf::Vector2f Board::getBoardSizeInPixels() const
{
	return sf::Vector2f(float(m_width * TILE_SIZE), float(m_height * TILE_SIZE));
}

sf::Vector2i Board::getBoardSizeInCoords() const
{
	return sf::Vector2i(m_width, m_height);
}

std::string Board::boardData()
{
    std::string data = "";
    data += "---Board---\n";
    data += m_name + "\n";
    data += "buildings:\n";
    for (auto& building : m_buildings) {
		data += building->buildingData();
        data += "\n";
	}
	return data;
}

