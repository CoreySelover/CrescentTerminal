#include "Building.h"
#include "Tile.h"

Building::Building(BuildingType type, bool hasInteriorMap) 
	: m_hasInteriorMap(hasInteriorMap)
{
	setBuildingType(type);
}

Building::~Building()
{
}

void Building::setBuildingType(BuildingType type)
{
	m_type = type;
	// TODO - should this be hardcoded or read from a file?
	switch (type)
	{
		case BuildingType_Base:
			m_footprintSize = sf::Vector2i(5, 5);
			resizeTiles();
			for (int i = 0; i < m_footprintSize.x; ++i)
			{
				for (int j = 0; j < m_footprintSize.y; ++j)
				{
					setTileType(sf::Vector2i(i, j), TileType_Wall);
				}
			}
			// Steel, plastic, glass
			m_requirements = BuildingRequirements{ 50, 50, 100 };
			break;
		default:
			break;
	}
}

void Building::resizeTiles()
{
	m_tilesAsTypes.resize(m_footprintSize.x);
	for (int i = 0; i < m_footprintSize.x; i++)
	{
		m_tilesAsTypes[i].resize(m_footprintSize.y);
	}
}

std::vector<std::pair<std::string, int>> Building::getCost() const
{
	std::vector<std::pair<std::string, int>> cost;
	cost.push_back(std::make_pair("steel", m_requirements.m_steel));
	cost.push_back(std::make_pair("plastic", m_requirements.m_plastic));
	cost.push_back(std::make_pair("glass", m_requirements.m_glass));
	return cost;
}

void Building::setTileType(sf::Vector2i position, TileType type)
{
	m_tilesAsTypes[position.x][position.y] = type;
}

TileType Building::getTileType(sf::Vector2i position) const
{
	return m_tilesAsTypes[position.x][position.y];
}