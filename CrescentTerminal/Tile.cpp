#include "Tile.h"
#include "Global.h"

Tile::Tile(TileType type, bool isObstacle)
	: m_isObstacle(isObstacle),
	m_buildEligible(false)
{
	setType(type);
	//TODO: Unhardcode
	m_sprite.setTexture(TextureManager::getTexture("Assets/World.png"));
	m_sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
}

void Tile::setObstacle(bool isObstacle)
{
	m_isObstacle = isObstacle;
}

bool Tile::isObstacle() const
{
	return m_isObstacle;
}

void Tile::setType(TileType type)
{
	m_type = type;

	switch (type) {
	case TileType_Empty:
		m_isObstacle = true;
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
		m_buildEligible = true;
		break;
	case TileType_Dirt:
		m_isObstacle = false;
		m_sprite.setTextureRect(sf::IntRect(0, 0, TILE_SIZE, TILE_SIZE));
		m_buildEligible = true;
		break;
	case TileType_Planter:
		m_isObstacle = false;
		break;
	default:
		m_isObstacle = false;
		break;
	}

}

TileType Tile::getType() const
{
	return m_type;
}

void Tile::setHighlight(bool isHighlighted)
{
	if (isHighlighted) {
		m_sprite.setColor(sf::Color(255, 255, 255, 128));
	}
	else {
		m_sprite.setColor(sf::Color(255, 255, 255, 255));
	}
}

void Tile::draw(sf::RenderWindow& window, sf::Vector2f position)
{
	m_sprite.setPosition(position);
	window.draw(m_sprite);
}





