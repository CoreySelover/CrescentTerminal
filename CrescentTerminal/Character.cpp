#include "Character.h"
#include "Global.h"
#include "Board.h"

#include <iostream>

Character::Character(std::string name, const Board& board) : Entity(name), m_board(board)
{
	m_walkSpeed = WALK_SPEED;
	m_direction = Direction::DOWN;
	m_walking = false;
	m_previousPosition = m_position;

	std::string filepath = "Assets/" + name + ".png";

	// Reminder - the float represents milliseconds per frame (thus the high numbers)
	// filepath, x, y, width, height, frames, milliseconds per frame
	m_animations["stop_down"] = std::make_shared<Animation>(filepath, 0, 0, 18, 27, 1, 100.0f);
	m_animations["stop_up"] = std::make_shared<Animation>(filepath, 18, 0, 18, 27, 1, 100.0f);
	m_animations["stop_right"] = std::make_shared<Animation>(filepath, 36, 0, 18, 27, 1, 100.0f);
	m_animations["stop_left"] = std::make_shared<Animation>(filepath, 54, 0, 18, 27, 1, 100.0f);
	m_animations["walk_down"] = std::make_shared<Animation>(filepath, 0, 0, 18, 27, 4, 100.0f);
	m_animations["walk_up"] = std::make_shared<Animation>(filepath, 0, 0, 18, 27, 4, 100.0f);
	m_animations["walk_left"] = std::make_shared<Animation>(filepath, 0, 0, 18, 27, 4, 100.0f);
	m_animations["walk_right"] = std::make_shared<Animation>(filepath, 0, 0, 18, 27, 4, 100.0f);
	m_currentAnimation = m_animations["stop_down"];
}

Character::~Character()
{
	m_animations.clear();
	m_currentAnimation = nullptr;
}

void Character::update(float deltaTime)
{
	Entity::update(deltaTime);

	m_previousPosition = m_position;

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
		
		sf::Vector2i proposedPosition = Board::pixelsToTile(m_position + velocity * deltaTime);

		if (m_board.isTileInBounds(proposedPosition.x, proposedPosition.y)
			&& !m_board.isTileObstacle(proposedPosition.x, proposedPosition.y))
		{
			movePosition(velocity * deltaTime);
		}
	}

	m_currentAnimation->update(deltaTime);
	m_currentAnimation->setPosition(m_position);
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

	switch (direction)
	{
		case Direction::UP:
			m_currentAnimation = m_animations["walk_up"];
			break;
		case Direction::DOWN:
			m_currentAnimation = m_animations["walk_down"];
			break;
		case Direction::LEFT:
			m_currentAnimation = m_animations["walk_left"];
			break;
		case Direction::RIGHT:
			m_currentAnimation = m_animations["walk_right"];
			break;
		default:
			throw("Invalid direction!");
			break;
	}
}

void Character::stopWalking()
{
	m_walking = false;
	
	switch (m_direction)
	{
	case Direction::UP:
		m_currentAnimation = m_animations["stop_up"];
		break;
	case Direction::DOWN:
		m_currentAnimation = m_animations["stop_down"];
		break;
	case Direction::LEFT:
		m_currentAnimation = m_animations["stop_left"];
		break;
	case Direction::RIGHT:
		m_currentAnimation = m_animations["stop_right"];
		break;
	default:
		throw("Invalid direction!");
		break;
	}
}

