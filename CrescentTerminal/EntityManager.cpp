#include "EntityManager.h"

// STD
#include <iostream>

EntityManager::EntityManager()
{
}

EntityManager::~EntityManager()
{
}

void EntityManager::addEntity(std::shared_ptr<Entity> entity) 
{
	m_entities[entity->getName()] = std::move(entity);
}

std::shared_ptr<Entity> EntityManager::getEntity(std::string entityName)
{
	return m_entities[entityName];
}

void EntityManager::removeEntity(std::string entityName)
{
	m_entities.erase(entityName);
}

void EntityManager::printEntities()
{
	for (auto& entity : m_entities)
	{
		std::cout << entity.second->getName() << std::endl;
	}
}

void EntityManager::drawEntities(sf::RenderWindow& window)
{
	for (auto& entity : m_entities)
	{
		entity.second->draw(window);
	}
}
