#include <iostream>

#include "Building.h"
#include "Tile.h"
#include "Board.h"

Building::Building(BuildingType type, std::string ownerName, sf::Vector2i tileCoords, bool interior)
	: m_ownerName(ownerName)
{
	setBuildingType(type);
	setBoardPosition(tileCoords);
	if (interior) buildInterior();
}

Building::~Building()
{
}

void Building::setBuildingType(BuildingType type)
{
	m_type = type;
	static const std::string buildingNames[] = { "Base", "Greenhouse", "Shed" };
	static int buildingCounts[] = {0, 0, 0};
	m_name = buildingNames[type] + std::to_string(buildingCounts[type]++);

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
			setTileType(sf::Vector2i(2, 4), TileType_Door);
			// Steel, plastic, glass
			m_requirements = BuildingRequirements{ 50, 50, 100 };
			m_buildBuffer = 1;
			break;
		default:
			m_buildBuffer = 0;
			break;
	}
}

void Building::buildInterior() {
	switch (m_type) {
	case BuildingType_Base:
		m_interior = std::make_shared<Board>(m_name + "_interior", 5, 5, BoardType_Interior, TileType_Floor);
		m_interior->getTile(2, 4).setType(TileType_Door);
		m_interior->addDoor(sf::Vector2i(2, 4), m_ownerName, m_boardPosition + sf::Vector2i(2, 5));
		break;
	default:
		break;
	}
}

void Building::setBoardPosition(sf::Vector2i position)
{
	m_boardPosition = position;
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