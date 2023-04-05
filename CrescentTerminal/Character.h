#pragma once

#include "Entity.h"
#include "Global.h"

class Character :
    public Entity
{
public:
	Character(std::string name);
	~Character();

	void update(float deltaTime);

	// Movement
	void setDirection(Direction direction) { m_direction = direction;  }
	void movePosition(sf::Vector2f movement);
	void walk(Direction direction);
	void stopWalking() { m_walking = false; }

private:
	float m_walkSpeed;
	bool m_walking;
	Direction m_direction;
};

