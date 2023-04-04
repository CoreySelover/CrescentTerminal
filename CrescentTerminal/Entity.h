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

	// Getters and Setters
	std::string getName();

private:
	std::string m_name;
};

