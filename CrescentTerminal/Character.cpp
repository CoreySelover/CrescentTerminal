#include "Character.h"
#include "Global.h"

Character::Character(std::string name) : Entity(name)
{
	m_walkSpeed = WALK_SPEED;
}

Character::~Character()
{
}

void Character::movePosition(sf::Vector2f movement)
{
	m_position += movement;
}
