#pragma once

// STD
#include <map>

// Crescent Terminal
#include "Entity.h"
#include "Global.h"
#include "Animation.h"

#include "Board.h"

class Character :
    public Entity
{
public:
	Character(std::string name, const Board& board);
	~Character();

	void update(float deltaTime);
	void draw(sf::RenderWindow& window);

	// Movement
	void setDirection(Direction direction) { m_direction = direction;  }
	void movePosition(sf::Vector2f movement);
	void walk(Direction direction);
	void stopWalking(Direction direction);
	bool canWalk(sf::Vector2f velocity);

private:
	const Board& m_board;

	float m_walkSpeed;
	bool m_walking;
	Direction m_direction;
	bool m_up;
	bool m_down;
	bool m_left;
	bool m_right;

	sf::IntRect m_hitBox;
	sf::RectangleShape m_hitBoxShape;

	std::map<std::string, std::shared_ptr<Animation>> m_animations;
	std::shared_ptr<Animation> m_currentAnimation;
};

