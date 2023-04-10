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
    sf::Vector2f viewCenter = window.getView().getCenter();
    sf::Vector2f viewSize = window.getView().getSize();
    if (m_position.x < 0 ||
        m_position.x < viewCenter.x - viewSize.x / 2  ||
        m_position.x > viewCenter.x + viewSize.x / 2 ||
        m_position.y < 0 ||
        m_position.y < viewCenter.y - viewSize.y / 2  ||
        m_position.y > viewCenter.y + viewSize.y / 2)
    {
        return false;
    }
    return true;
}