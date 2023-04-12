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
        bool isObstacle = false)
        : m_isObstacle(isObstacle)
    {
        setType(type);
		//TODO: Unhardcode
		m_sprite.setTexture(TextureManager::getTexture("Assets/World.png"));
		m_sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
    }

    void setObstacle(bool isObstacle) {
        m_isObstacle = isObstacle;
    }

    bool isObstacle() const {
        return m_isObstacle;
    }

    void setType(TileType type) {
		m_type = type;

        switch (type) {
            case TileType_Empty:
				m_isObstacle = false;
				break;
			case TileType_Wall:
				m_isObstacle = true;
				break;
			case TileType_Floor:
				m_isObstacle = false;
				break;
			case TileType_Door:
				m_isObstacle = true;
				break;
			case TileType_Stairs:
				m_isObstacle = false;
				break;
			case TileType_Grass:
				m_isObstacle = false;
				break;
			case TileType_Dirt:
				m_isObstacle = false;
				m_sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
				break;
			case TileType_Planter:
				m_isObstacle = true;
				break;
			default:
				m_isObstacle = false;
				break;
        }
	}

    TileType getType() const {
        return m_type;
    }

    // TODO: Draw sprites instead of rectangles
    void draw(sf::RenderWindow& window, sf::Vector2f position) {
        m_sprite.setPosition(position);
        window.draw(m_sprite);
    }

private:
    bool m_isObstacle;
    TileType m_type;
    sf::Sprite m_sprite;
};


