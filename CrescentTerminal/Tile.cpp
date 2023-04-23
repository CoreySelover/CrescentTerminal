#include "Tile.h"
#include "Global.h"

Tile::Tile(TileType type, bool isObstacle)
	: m_isObstacle(isObstacle),
	m_buildEligible(false)
{
	setType(type);
	//TODO: Unhardcode
	m_sprite.setTexture(TextureManager::getTexture("Assets/Maps/tile_set_base.png"));
	m_sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));

	m_highlight.setFillColor(sf::Color::Transparent);
	m_highlight.setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));
}

void Tile::setObstacle(bool isObstacle)
{
	m_isObstacle = isObstacle;
}

bool Tile::isObstacle() const
{
	return m_isObstacle;
}

bool Tile::isBuildEligible() const
{
	return m_buildEligible;
}

void Tile::setType(TileType type)
{
	m_type = type;

	switch (type) {
	case TileType_Empty:
		m_isObstacle = true;
		m_buildEligible = false;
		break;
	case TileType_Wall:
		m_isObstacle = true;
		m_buildEligible = false;
		break;
	case TileType_Floor:
		m_isObstacle = false;
		m_buildEligible = true;
		break;
	case TileType_Door:
		m_isObstacle = false;
		m_buildEligible = false;
		break;
	default:
		m_isObstacle = false;
		m_buildEligible = false;
		break;
	}

}

void Tile::setTextureRect(sf::IntRect rect)
{
	m_sprite.setTextureRect(rect);
}

TileType Tile::getType() const
{
	return m_type;
}

void Tile::setHighlight(sf::Color color)
{
	m_highlight.setFillColor(color);
	if (color != sf::Color::Transparent)
		m_highlight.setFillColor(sf::Color(color.r, color.g, color.b, 100));
}

void Tile::draw(sf::RenderWindow& window, sf::Vector2f position)
{
	m_sprite.setPosition(position);
	m_highlight.setPosition(position);
	window.draw(m_sprite);
	window.draw(m_highlight);
}





