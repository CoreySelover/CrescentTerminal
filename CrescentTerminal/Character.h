#pragma once

#include "Entity.h"
class Character :
    public Entity
{
public:
	Character(std::string name);
	~Character();

	// Movement
	void movePosition(sf::Vector2f movement);

private:
	float m_walkSpeed;
};

