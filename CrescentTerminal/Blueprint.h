#pragma once

#include <string>
#include <map>
#include <vector>

class Tile;

class Blueprint
{
public:
	Blueprint(std::string name, std::string filepath);
	~Blueprint();
	std::map<std::string, std::vector<std::vector<Tile>>> getTiles();
	sf::Vector2i getFootprintSize() const { return m_footprintSize; }

private:
	std::string m_name;
	std::map<std::string, std::vector<std::vector<Tile>>> m_tiles;
	sf::Vector2i m_footprintSize;
};

