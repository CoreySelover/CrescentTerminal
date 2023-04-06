#include "Character.h"
#include "Global.h"
#include "Board.h"

#include <iostream>

Character::Character(std::string name, const Board& board) : Entity(name), m_board(board)
{
	m_walkSpeed = WALK_SPEED;
	m_direction = Direction::DOWN;
	m_walking = false;

	std::string filepath = "Assets/" + name + ".png";

	// TODO - unhardcode this
	sf::Vector2i spriteSize(18, 27);
	int sX = spriteSize.x;
	int sY = spriteSize.y;
	m_hitBox = sf::IntRect(0, 0, sX, sY * 2/3);

	m_hitBoxShape.setPosition(m_hitBox.left, m_hitBox.top);
	m_hitBoxShape.setSize(sf::Vector2f(m_hitBox.width, m_hitBox.height));
	m_hitBoxShape.setFillColor(sf::Color::Transparent);
	m_hitBoxShape.setOutlineColor(sf::Color::Red);
	m_hitBoxShape.setOutlineThickness(1.0f);

	// Reminder - the float represents milliseconds per frame (thus the high numbers)
	// filepath, x, y, width, height, frames, milliseconds per frame
	m_animations["stop_down"] = std::make_shared<Animation>(filepath, 0, 0, sX, sY, 1, 100.0f);
	m_animations["stop_up"] = std::make_shared<Animation>(filepath, 18, 0, sX, sY, 1, 100.0f);
	m_animations["stop_right"] = std::make_shared<Animation>(filepath, 36, 0, sX, sY, 1, 100.0f);
	m_animations["stop_left"] = std::make_shared<Animation>(filepath, 54, 0, sX, sY, 1, 100.0f);
	m_animations["walk_down"] = std::make_shared<Animation>(filepath, 0, 0, sX, sY, 4, 100.0f);
	m_animations["walk_up"] = std::make_shared<Animation>(filepath, 0, 0, sX, sY, 4, 100.0f);
	m_animations["walk_left"] = std::make_shared<Animation>(filepath, 0, 0, sX, sY, 4, 100.0f);
	m_animations["walk_right"] = std::make_shared<Animation>(filepath, 0, 0, sX, sY, 4, 100.0f);
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

	m_hitBox.left = m_position.x;
	m_hitBox.top = m_position.y + m_currentAnimation->getSize().y - m_hitBox.height;
	m_hitBoxShape.setPosition(m_hitBox.left, m_hitBox.top);
}

void Character::draw(sf::RenderWindow& window)
{
	m_currentAnimation->draw(window);

	if (DEBUG_DRAW) {
		window.draw(m_hitBoxShape);
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

