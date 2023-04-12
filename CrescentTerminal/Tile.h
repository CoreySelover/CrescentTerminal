#pragma once

#include <SFML/Graphics.hpp>

#include "TextureManager.h"

enum TileType {
	TileType_Empty,
	TileType_Wall,
	TileType_Floor,
	TileType_Door,
	TileType_Stairs,
    TileType_Grass,
    TileType_Dirt,
    TileType_Planter,
	TileType_Count
};;

class Tile {
public:
	Tile(TileType type = TileType_Floor,
		bool isObstacle = false);

	void setObstacle(bool isObstacle);

	bool isObstacle() const;

    void setType(TileType type);

	void setHighlight(bool isHighlighted);

    TileType getType() const;

	void draw(sf::RenderWindow& window, sf::Vector2f position);

private:
    bool m_isObstacle;
	bool m_buildEligible;
    TileType m_type;
    sf::Sprite m_sprite;
};


