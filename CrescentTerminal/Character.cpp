#include "Character.h"

Character::Character(std::string name,
	sf::Vector2f initialPosition,
	bool controllable) : Entity(name), 
		m_position(initialPosition),
		m_controllableByUser(controllable)
{
}

Character::~Character()
{
}

void Character::movePosition(sf::Vector2f movement)
{
	m_position += movement;
}

void Character::setControllableByUser(bool controllable)
{
	m_controllableByUser = controllable;
}

sf::Vector2f Character::getPosition()
{
	return m_position;
}
