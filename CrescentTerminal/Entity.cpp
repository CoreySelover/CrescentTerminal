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