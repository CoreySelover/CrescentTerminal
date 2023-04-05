#include "Character.h"
#include "Global.h"

#include <iostream>

Character::Character(std::string name) : Entity(name)
{
	m_walkSpeed = WALK_SPEED;
	m_direction = Direction::DOWN;
	m_walking = false;

	std::string filepath = "Assets/" + name + ".png";

	m_anim_stop = std::make_shared<Animation>(filepath, 0, 0, 32, 32, 1, 0.2f);
	m_anim_walk = std::make_shared<Animation>(filepath, 0, 0, 32, 32, 4, 0.2f);
}

Character::~Character()
{
}

void Character::update(float deltaTime)
{
	Entity::update(deltaTime);

	// TODO
	m_anim_stop->update(deltaTime);
	m_anim_stop->setPosition(m_position);

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
	m_anim_stop->draw(window);
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

