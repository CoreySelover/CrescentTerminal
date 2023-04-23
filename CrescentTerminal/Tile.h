#pragma once

#include <SFML/Graphics.hpp>

#include "TextureManager.h"

enum TileType {
	TileType_Empty,
	TileType_Floor,
	TileType_Wall,
	TileType_Door,
	TileType_Count
};;

class Tile {
public:
	Tile(TileType type = TileType_Floor,
		bool isObstacle = false);

	void setObstacle(bool isObstacle);

	bool isObstacle() const;

	bool isBuildEligible() const;

    void setType(TileType type);

	void setTextureRect(sf::IntRect rect);

	void setHighlight(sf::Color color);

    TileType getType() const;

	void draw(sf::RenderWindow& window, sf::Vector2f position);

private:
    bool m_isObstacle;
	bool m_buildEligible;
    TileType m_type;
    sf::Sprite m_sprite;
	sf::RectangleShape m_highlight;
};


