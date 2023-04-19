#include "Building.h"

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
			for (int i = 0; i < m_footprintSize.x; i++)
			{
				for (int j = 0; j < m_footprintSize.y; j++)
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
	m_tiles.resize(m_footprintSize.x);
	for (int i = 0; i < m_footprintSize.x; i++)
	{
		m_tiles[i].resize(m_footprintSize.y);
	}
}

void Building::setTileType(sf::Vector2i position, TileType type)
{
	m_tiles[position.x][position.y] = type;
}