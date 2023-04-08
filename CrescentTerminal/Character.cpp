#include "Character.h"
#include "Global.h"
#include "Board.h"

#include <iostream>

Character::Character(std::string name, std::shared_ptr<Board> board) : Entity(name), m_board(board)
{
	m_walkSpeed = WALK_SPEED;
	m_direction = Direction::DOWN;
	m_walking = false;
	m_down = false;
	m_up = false;
	m_left = false;
	m_right = false;

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

		if (canWalk(velocity * deltaTime))
		{
			movePosition(velocity * deltaTime);
		}

		m_hitBox.left = m_position.x;
		m_hitBox.top = m_position.y + m_currentAnimation->getSize().y - m_hitBox.height;
		m_hitBoxShape.setPosition(m_hitBox.left, m_hitBox.top);

	}

	m_currentAnimation->update(deltaTime);
	m_currentAnimation->setPosition(m_position);
}


bool Character::canWalk(sf::Vector2f velocity)
{
	// Check top left corner
	sf::Vector2i proposedTile1 = m_board->pixelsToTileCoords(sf::Vector2f(m_hitBox.left + velocity.x, m_hitBox.top + velocity.y));

	if (!m_board->isTileInBounds(proposedTile1.x, proposedTile1.y)
		|| m_board->isTileObstacle(proposedTile1.x, proposedTile1.y))
	{
		return false;
	}

	// Check top right corner
	sf::Vector2i proposedTile2 = m_board->pixelsToTileCoords(sf::Vector2f(m_hitBox.left + m_hitBox.width + velocity.x, m_hitBox.top + velocity.y));

	if (!m_board->isTileInBounds(proposedTile2.x, proposedTile2.y)
		|| m_board->isTileObstacle(proposedTile2.x, proposedTile2.y))
	{
		return false;
	}

	// Check bottom left corner
	sf::Vector2i proposedTile3 = m_board->pixelsToTileCoords(sf::Vector2f(m_hitBox.left + velocity.x, m_hitBox.top + m_hitBox.height + velocity.y));

	if (!m_board->isTileInBounds(proposedTile3.x, proposedTile3.y)
		|| m_board->isTileObstacle(proposedTile3.x, proposedTile3.y))
	{
		return false;
	}

	// Check bottom right corner
	sf::Vector2i proposedTile4 = m_board->pixelsToTileCoords(sf::Vector2f(m_hitBox.left + m_hitBox.width + velocity.x, m_hitBox.top + m_hitBox.height + velocity.y));

	if (!m_board->isTileInBounds(proposedTile4.x, proposedTile4.y)
		|| m_board->isTileObstacle(proposedTile4.x, proposedTile4.y))
	{
		return false;
	}

	return true;
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
			m_up = true;
			break;
		case Direction::DOWN:
			m_currentAnimation = m_animations["walk_down"];
			m_down = true;
			break;
		case Direction::LEFT:
			m_currentAnimation = m_animations["walk_left"];
			m_left = true;
			break;
		case Direction::RIGHT:
			m_currentAnimation = m_animations["walk_right"];
			m_right = true;
			break;
		default:
			throw std::invalid_argument("Invalid direction!");
			break;
	}
}

void Character::stopWalking(Direction direction)
{
	switch (direction)
	{
	case Direction::UP:
		m_up = false;
		break;
	case Direction::DOWN:
		m_down = false;
		break;
	case Direction::LEFT:
		m_left = false;
		break;
	case Direction::RIGHT:
		m_right = false;
		break;
	default:
		throw std::invalid_argument("Invalid direction!");
		break;
	}

	if (!m_up && !m_down && !m_left && !m_right)
	{
		m_walking = false;
		m_currentAnimation = m_animations["stop_" + directionToString(m_direction)];
	}
	else if (m_up) { walk(UP); }
	else if (m_down) { walk(DOWN); }
	else if (m_left) { walk(LEFT); }
	else if (m_right) { walk(RIGHT); }
}

