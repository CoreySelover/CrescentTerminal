#include "Entity.h"

Entity::Entity(std::string name) : m_name(name)
{
}

Entity::~Entity()
{
}

void Entity::draw(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}

std::string Entity::getName()
{
	return m_name;
}
