#pragma once

// STD
#include <map>

// Crescent Terminal
#include "Entity.h"
#include "Global.h"

class Board;
class Animation;

class Character :
    public Entity
{
public:
	Character(std::string name, std::shared_ptr<Board> board);
	~Character();

	void update(float deltaTime);
	bool isOnScreen(sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);
	void setBoard(std::shared_ptr<Board> board);

	// Movement
	void checkForCollisions();
	void setDirection(Direction direction) { m_direction = direction; }
	Direction getDirection() { return m_direction; }
	void movePosition(sf::Vector2f movement);
	void walk(Direction direction);
	void stopWalking(Direction direction);
	void stopCompletely();
	bool canWalk(sf::Vector2f velocity);

private:
	std::shared_ptr<Board> m_board;

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

