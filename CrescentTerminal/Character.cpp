#include "Character.h"

Character::Character(std::string name,
	bool controllable) : Entity(name), 
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

bool Character::isControllableByUser()
{
	return m_controllableByUser;
}
