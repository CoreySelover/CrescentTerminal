#include "Entity.h"

#include <iostream>

Entity::Entity(std::string name) : m_name(name)
{
}

Entity::~Entity()
{
}

void Entity::update(float deltaTime)
{

}

void Entity::draw(sf::RenderWindow& window)
{

}

std::string Entity::getName()
{
	return m_name;
}

void Entity::setPosition(sf::Vector2f position)
{
	m_position = position;
}

sf::Vector2f Entity::getPosition()
{
	return m_position;
}

bool Entity::isOnScreen(sf::RenderWindow& window)
{
	sf::Vector2f windowSize = sf::Vector2f(window.getSize());
	sf::Vector2f position = getPosition();
	if (position.x < 0 || position.x > windowSize.x || position.y < 0 || position.y > windowSize.y)
	{
		return false;
	}
	return true;
}