#pragma once

// STD
#include <memory>
#include <map>

// SFML

// Crescent Terminal
#include "Entity.h"

class EntityManager
{
public:
	EntityManager();
	~EntityManager();

	void addEntity(std::unique_ptr<Entity> entity);
	std::unique_ptr<Entity> getEntity(std::string entityName);
	void removeEntity(std::string entityName);
	void printEntities();

private:
	std::map<std::string, std::unique_ptr<Entity>> m_entities;
};

