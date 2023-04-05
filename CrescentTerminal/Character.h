#pragma once

#include "Entity.h"
#include "Global.h"

// Crescent Terminal
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
	void stopWalking() { m_walking = false; }

private:
	float m_walkSpeed;
	bool m_walking;
	Direction m_direction;

	std::shared_ptr<Animation> m_anim_walk;
	std::shared_ptr<Animation> m_anim_stop;
};

