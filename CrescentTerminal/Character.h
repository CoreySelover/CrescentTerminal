#pragma once

#include "Entity.h"
class Character :
    public Entity
{
public:
	Character(std::string name,
		bool controllable = false);
	~Character();

	// Movement
	void movePosition(sf::Vector2f movement);

	// Getters and Setters
	void setControllableByUser(bool controllable);
	bool isControllableByUser();	

private:
	bool m_controllableByUser;
};

