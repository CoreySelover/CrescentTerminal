#pragma once

#include "Entity.h"
#include "Global.h"

class Character :
    public Entity
{
public:
	Character(std::string name);
	~Character();

	// Movement
	void setDirection(Direction direction) { m_direction = direction;  }
	void movePosition(sf::Vector2f movement);
	void walk(Direction direction);

private:
	float m_walkSpeed;
	Direction m_direction;
};

