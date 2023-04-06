#pragma once

// STD
#include <map>

// Crescent Terminal
#include "Entity.h"
#include "Global.h"
#include "Animation.h"

class Character :
    public Entity
{
public:
	Character(std::string name);
	~Character();

	void update(float deltaTime);
	void draw(sf::RenderWindow& window);

	// Movement
	void setDirection(Direction direction) { m_direction = direction;  }
	void movePosition(sf::Vector2f movement);
	void walk(Direction direction);
	void stopWalking();

private:
	float m_walkSpeed;
	bool m_walking;
	Direction m_direction;

	std::map<std::string, std::shared_ptr<Animation>> m_animations;
	std::shared_ptr<Animation> m_currentAnimation;
};

