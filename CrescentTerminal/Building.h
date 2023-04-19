#pragma once

#include <vector>
#include <string>

#include <SFML/System/Vector2.hpp>

//#include "Board.h"

enum BuildingType {
	BuildingType_Base,
	BuildingType_Greenhouse,
	BuildingType_Shed,
	BuildingType_Count
};

struct BuildingRequirements {
	int m_steel;
	int m_plastic;
	int m_glass;
};

enum TileType;

class Building
{
public:
	Building(BuildingType type = BuildingType_Base, bool hasInteriorMap = false);
	~Building();
	void setBuildingType(BuildingType type);
	BuildingType getBuildingType() const { return m_type; }
	sf::Vector2i getFootprintSize() const { return m_footprintSize; }
		void resizeTiles();
	std::vector<std::pair<std::string, int>> getCost() const;
	TileType getTileType(sf::Vector2i position) const;

private:
	void setTileType(sf::Vector2i position, TileType type);

	BuildingType m_type;
	BuildingRequirements m_requirements;
	sf::Vector2i m_footprintSize;
	std::vector<std::vector <TileType> > m_tilesAsTypes;
	bool m_hasInteriorMap;
};

