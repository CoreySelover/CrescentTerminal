#pragma once

// STD
#include <memory>
#include <map>

// SFML
#include <SFML/Graphics.hpp>

// Crescent Terminal
#include "Entity.h"

class EntityManager
{
public:
	EntityManager();
	~EntityManager();

	void update(float deltaTime);
	void drawEntities(sf::RenderWindow& window);

	void addEntity(std::shared_ptr<Entity> entity);
	std::shared_ptr<Entity> getEntity(std::string entityName);
	void removeEntity(std::string entityName);
	void printEntities();

private:
	std::map<std::string, std::shared_ptr<Entity>> m_entities;
};

