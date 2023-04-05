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

void Character::update(float deltaTime)
{
	Entity::update(deltaTime);

	if (m_walking)
	{
		sf::Vector2f velocity(0.0f, 0.0f);

		switch (m_direction)
		{
		case Direction::UP:
			velocity.y -= m_walkSpeed;
			break;
		case Direction::DOWN:
			velocity.y += m_walkSpeed;
			break;
		case Direction::LEFT:
			velocity.x -= m_walkSpeed;
			break;
		case Direction::RIGHT:
			velocity.x += m_walkSpeed;
			break;
		}

		movePosition(velocity * deltaTime);
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
