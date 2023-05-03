#include <iostream>

#include "Building.h"
#include "Tile.h"
#include "Board.h"
#include "Global.h"
#include "BoardManager.h"
#include "Blueprint.h"

Building::Building(BuildingType type, std::string ownerName, sf::Vector2i tileCoords, bool interior)
	: m_ownerName(ownerName)
{
	setBuildingType(type);
	loadBlueprint();
	setBoardPosition(tileCoords);
	if (interior) buildInterior();
}

Building::~Building()
{
	m_tiles.clear();
}

void Building::setBuildingType(BuildingType type)
{
	m_type = type;
	static const std::string buildingNames[] = { "Base", "Greenhouse", "Shed" };
	static int buildingCounts[] = {0, 0, 0};
	m_name = buildingNames[type] + std::to_string(buildingCounts[type]++);
}

void Building::loadBlueprint() {
	
	std::shared_ptr<Blueprint> blueprint;

	switch (m_type)
	{
	case BuildingType_Base:
		blueprint = BoardManager::getInstance().getBlueprint("Base_Blueprint");
		// Steel, plastic, glass
		m_requirements = BuildingRequirements{ 50, 50, 100 };
		m_buildBuffer = 0;
		break;
	case BuildingType_Shed:
		blueprint = BoardManager::getInstance().getBlueprint("Shed_Blueprint");
		// Steel, plastic, glass
		m_requirements = BuildingRequirements{ 20, 20, 0 };
		m_buildBuffer = 0;
		break;
	default:
		m_buildBuffer = 0;
		break;
	}

	m_footprintSize = blueprint->getFootprintSize();
	m_tiles = blueprint->getTiles();
}

void Building::buildInterior() {
	switch (m_type) {
	case BuildingType_Base:
		m_interior = std::make_shared<Board>(m_name + "_Interior", "Assets/Maps/Base_Interior.xml");
		// TODO - unhardcode this.  This is the door to the outside
		m_interior->addDoor(sf::Vector2i(2, 6), m_ownerName, m_boardPosition + sf::Vector2i(2,5));
		break;
	case BuildingType_Shed:
		m_interior = std::make_shared<Board>(m_name + "_Interior", "Assets/Maps/Shed_Interior.xml");
		// TODO - unhardcode this.  This is the door to the outside
		m_interior->addDoor(sf::Vector2i(2, 4), m_ownerName, m_boardPosition + sf::Vector2i(int(m_footprintSize.x / 2), int(m_footprintSize.y)));
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
	for (auto& layer : m_tiles) {
		layer.second.resize(m_footprintSize.x);
		for (int x = 0; x < m_footprintSize.x; ++x) {
			layer.second[x].resize(m_footprintSize.y);
		}
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

Tile Building::getTile(std::string layerName, sf::Vector2i position) const
{
	// return the tile type at the given position on the given layer
	return m_tiles.at(layerName).at(position.x).at(position.y);
}