#include "Character.h"
#include "Global.h"

#include <iostream>

Character::Character(std::string name) : Entity(name)
{
	m_walkSpeed = WALK_SPEED;
	m_direction = Direction::DOWN;
	m_walking = false;

	std::string filepath = "Assets/" + name + ".png";

	// Reminder - the float represents milliseconds per frame (thus the high numbers)
	// filepath, x, y, width, height, frames, milliseconds per frame
	m_animations["stop"] = std::make_shared<Animation>(filepath, 0, 0, 18, 27, 1, 100.0f);
	m_animations["walk"] = std::make_shared<Animation>(filepath, 0, 0, 18, 27, 4, 100.0f);
	m_currentAnimation = m_animations["stop"];
}

Character::~Character()
{
	m_animations.clear();
	m_currentAnimation = nullptr;
}

void Character::update(float deltaTime)
{
	Entity::update(deltaTime);

	m_currentAnimation->update(deltaTime);
	m_currentAnimation->setPosition(m_position);

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

void Character::draw(sf::RenderWindow& window)
{
	m_currentAnimation->draw(window);
}

void Character::movePosition(sf::Vector2f movement)
{
	m_position += movement;
}

void Character::walk(Direction direction)
{
	setDirection(direction);
	m_walking = true;
	m_currentAnimation = m_animations["walk"];
}

void Character::stopWalking()
{
	m_walking = false;
	m_currentAnimation = m_animations["stop"];
}

