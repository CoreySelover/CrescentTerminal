#include "Entity.h"

#include <iostream>

Entity::Entity(std::string name) : m_name(name)
{
}

Entity::~Entity()
{
}

std::string Entity::getName()
{
	return m_name;
}
