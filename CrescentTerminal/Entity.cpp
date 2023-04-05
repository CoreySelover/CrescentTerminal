#include "Entity.h"

#include <iostream>

Entity::Entity(std::string name) : m_name(name)
{
}

Entity::~Entity()
{
}

bool Entity::loadTexture(std::string filepath)
{
	if (!m_texture.loadFromFile(filepath))
	{
		std::cout << "Failed to load texture: " << filepath << std::endl;
		return false;
	}
	m_sprite.setTexture(m_texture);
	return true;
}

void Entity::update(float deltaTime)
{
	m_sprite.setPosition(m_position);
}

void Entity::draw(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}

std::string Entity::getName()
{
	return m_name;
}

void Entity::setPosition(sf::Vector2f position)
{
}
