#include "Character.h"
#include "Global.h"

Character::Character(std::string name) : Entity(name)
{
	m_walkSpeed = WALK_SPEED;
	m_direction = Direction::DOWN;
}

Character::~Character()
{
}

void Character::movePosition(sf::Vector2f movement)
{
	m_position += movement;
}

void Character::walk(Direction direction)
{
	setDirection(direction);

	switch (direction)
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
