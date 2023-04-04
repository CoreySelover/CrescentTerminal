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
	bool loadTexture(std::string filepath);

	void update() {}
	void draw(sf::RenderWindow& window);

	// Getters and Setters
	std::string getName();

private:
	std::string m_name;
	sf::Texture m_texture;
	sf::Sprite m_sprite;
};

