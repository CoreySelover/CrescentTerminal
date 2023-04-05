#pragma once

// STD
#include <string>

// SFML
#include <SFML/Graphics.hpp>

class Entity
{
public:
	Entity(std::string name);
	~Entity();

	virtual void update(float deltaTime) = 0;
	virtual void draw(sf::RenderWindow& window) = 0;

	// Getters and Setters
	std::string getName();
	sf::Vector2f getPosition();
	void setPosition(sf::Vector2f position);

protected:
	sf::Vector2f m_position;

private:
	std::string m_name;
};

