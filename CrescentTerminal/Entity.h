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

	void update() {}
	void draw(sf::RenderWindow& window);

	// Getters and Setters
	std::string getName();

private:
	std::string m_name;
	sf::Sprite m_sprite;
};

