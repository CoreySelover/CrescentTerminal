#include "EntityManager.h"

// STD
#include <iostream>

EntityManager::EntityManager()
{
}

EntityManager::~EntityManager()
{
}

void EntityManager::addEntity(std::unique_ptr<Entity> entity) 
{
	m_entities[entity->getName()] = std::move(entity);
}

void EntityManager::printEntities()
{
	for (auto& entity : m_entities)
	{
		std::cout << entity.second->getName() << std::endl;
	}
}

