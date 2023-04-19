#include "Inventory.h"

#include <stdexcept>

Inventory::Inventory()
{
	// TODO - read from file
	m_steel = 5000;
	m_plastic = 5000;
	m_glass = 1000;
}

Inventory::~Inventory()
{
}

void Inventory::addResource(std::string resource, int amount)
{
	if (resource == "steel") { m_steel += amount; }
	else if (resource == "plastic") { m_plastic += amount; }
	else if (resource == "glass") { m_glass += amount; }
	else { throw std::invalid_argument("Invalid resource name"); }
}

void Inventory::removeResource(std::string resource, int amount)
{
	if (resource == "steel") { m_steel -= amount; }
	else if (resource == "plastic") { m_plastic -= amount; }
	else if (resource == "glass") { m_glass -= amount; }
	else { throw std::invalid_argument("Invalid resource name"); }
}

void Inventory::addResources(std::vector<std::pair<std::string, int>> resources)
{
	for (auto& resource : resources)
	{
		addResource(resource.first, resource.second);
	}
}

void Inventory::removeResources(std::vector<std::pair<std::string, int>> resources)
{
	for (auto& resource : resources)
	{
		removeResource(resource.first, resource.second);
	}
}

int Inventory::getAmountOf(std::string resource) const {
	if (resource == "steel") { return m_steel; }
	else if (resource == "plastic") { return m_plastic; }
	else if (resource == "glass") { return m_glass; }
	
	throw std::invalid_argument("Invalid resource name");
}

bool Inventory::doWeHaveEnough(std::string resource, int amount) const {
	return getAmountOf(resource) >= amount;
}

bool Inventory::doWeHaveEnough(std::vector<std::pair<std::string, int>> requirements) const {
	for (auto& requirement : requirements)
	{
		if (getAmountOf(requirement.first) < requirement.second)
		{
			return false;
		}
	}
	return true;
}