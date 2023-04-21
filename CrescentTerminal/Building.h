#pragma once

#include <vector>
#include <string>
#include <memory>

#include <SFML/System/Vector2.hpp>

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
class Board;

class Building
{
public:
	Building(BuildingType type, std::string ownerName, sf::Vector2i tileCoords = sf::Vector2i(), bool interior = false);
	~Building();

	// Building actions
	void buildInterior();
	std::shared_ptr<Board> getInterior() const { return m_interior; }

	// Building properties
	void setBuildingType(BuildingType type);
	void setBoardPosition(sf::Vector2i position);
	BuildingType getBuildingType() const { return m_type; }
	sf::Vector2i getFootprintSize() const { return m_footprintSize; }
		void resizeTiles();
	int getBuildBuffer() const { return m_buildBuffer; }
	std::vector<std::pair<std::string, int>> getCost() const;

	// Tile properties
	TileType getTileType(sf::Vector2i position) const;

private:
	void setTileType(sf::Vector2i position, TileType type);

	std::string m_ownerName;
	std::string m_name;
	BuildingType m_type;
	sf::Vector2i m_boardPosition;
	BuildingRequirements m_requirements;
	sf::Vector2i m_footprintSize;
	int m_buildBuffer;
	std::vector<std::vector <TileType> > m_tilesAsTypes;

	// Interior
	std::shared_ptr<Board> m_interior;
};

