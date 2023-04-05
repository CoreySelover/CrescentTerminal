#include "Character.h"
#include "Global.h"

#include <iostream>

Character::Character(std::string name) : Entity(name)
{
	m_walkSpeed = WALK_SPEED;
	m_direction = Direction::DOWN;
	m_walking = false;
}

Character::~Character()
{
}

void Character::update() 
{
	Entity::update();

	if (m_walking)
	{
		switch (m_direction)
		{
		case Direction::UP:
			movePosition(sf::Vector2f(0, -m_walkSpeed));
			break;
		case Direction::DOWN:
			movePosition(sf::Vector2f(0, m_walkSpeed));
			break;
		case Direction::LEFT:
			movePosition(sf::Vector2f(-m_walkSpeed, 0));
			break;
		case Direction::RIGHT:
			movePosition(sf::Vector2f(m_walkSpeed, 0));
			break;
		}
	}
}

void Character::movePosition(sf::Vector2f movement)
{
	m_position += movement;
}

void Character::walk(Direction direction)
{
	setDirection(direction);
	m_walking = true;
}
