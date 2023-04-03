#pragma once

#include "Entity.h"
class Character :
    public Entity
{
public:
	Character(std::string name,
		sf::Vector2f initialPosition = sf::Vector2f(),
		bool controllable = false);
	~Character();

	// Movement
	void movePosition(sf::Vector2f movement);

	// Getters and Setters
	void setControllableByUser(bool controllable);

private:
	bool m_controllableByUser;
	sf::Vector2f m_position;
};

