#include <iostream>

#include "pugixml.hpp"

#include "Global.h"
#include "Blueprint.h"
#include "Tile.h"

Blueprint::Blueprint(std::string name, std::string filepath)
	: m_name(name)
{
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(filepath.c_str());
	if (result)
	{
		pugi::xml_node blueprint = doc.child("map");
		m_footprintSize = sf::Vector2i(blueprint.attribute("width").as_int(), blueprint.attribute("height").as_int());

		for (pugi::xml_node layer = blueprint.child("layer"); layer; layer = layer.next_sibling("layer"))
		{
            std::string layerName = layer.attribute("name").as_string();

            // Resize the vector to fit the blueprint
            m_tiles[layerName].resize(m_footprintSize.x);
            for (int x = 0; x < m_footprintSize.x; x++) {
				m_tiles[layerName][x].resize(m_footprintSize.y);
			}

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
                    m_tiles[layerName][x][y].setType(TileType_Empty);
                }
                // Obstacles
                else if (layerName == "Obstacles") {
                    m_tiles["Obstacles"][x][y].setObstacle(true);
                    m_tiles["Obstacles"][x][y].setType(TileType_Wall);
                }

                // Texture rects
                int tileIndex = id - 1; // adjust index to start at 0
                int tileX = tileIndex % textureWidth;
                int tileY = tileIndex / textureWidth;
                sf::IntRect textureRect(tileX * TILE_SIZE, tileY * TILE_SIZE, TILE_SIZE, TILE_SIZE);
                m_tiles[layerName][x][y].setTextureRect(textureRect);

                // Next column and/or row
                x++;
                if (x == blueprint.attribute("width").as_int()) {
                    x = 0;
                    y++;
                }
            }
        }
	}
	else
	{
		std::cout << "Error loading blueprint: " << filepath << std::endl;
		std::cout << "Error description: " << result.description() << std::endl;
	}
}

Blueprint::~Blueprint()
{
}

std::map<std::string, std::vector<std::vector<Tile>>> Blueprint::getTiles()
{
	return m_tiles;
}