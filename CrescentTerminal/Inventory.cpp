#include "Inventory.h"

#include <stdexcept>
#include <iostream>

#include "Item.h"

Inventory::Inventory()
{
	// TODO - read from file
	m_steel = 5000;
	m_plastic = 5000;
	m_glass = 1000;

	m_items.resize(10);
	for (auto& row : m_items)
	{
		row.resize(3);
	}
}

Inventory::~Inventory()
{
	// Delete all items
	for (auto& row : m_items)
	{
		row.clear();
	}
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

bool Inventory::addItem(std::shared_ptr<Item> item, sf::Vector2i position)
{
	// Check that item slot exists
	if (position.x >= int(m_items.size()) || position.y >= int(m_items[0].size()) || position.x < -1
		|| position.y < -1)
	{
		throw std::invalid_argument("Invalid position");
	}
	if (position.x == -1 && position.y == -1)
	{
		// Find first empty slot
		for (int i = 0; i < m_items.size(); i++)
		{
			for (int j = 0; j < m_items[i].size(); j++)
			{
				if (m_items[i][j] == nullptr)
				{
					m_items[i][j] = item;
					item->setInventoryPosition(sf::Vector2i(i, j));
					return true;
				}
			}
		}
		// No empty slots found.
		return false;
	}
	else
	{
		if (m_items[position.x][position.y] != nullptr)
		{
			return false;
		}
		m_items[position.x][position.y] = item;
		item->setInventoryPosition(position);
		return true;
	}
}

std::shared_ptr<Item> Inventory::removeItemAtPosition(sf::Vector2i position)
{
	if (position.x >= m_items.size() || position.y >= m_items[0].size() || position.x < 0 || position.y < 0)
	{
		throw std::invalid_argument("Invalid position");
	}
	auto item = m_items[position.x][position.y];
	m_items[position.x][position.y] = nullptr;
	return item;
}

std::shared_ptr<Item> Inventory::getItemAtPosition(sf::Vector2i position) const
{
	if (position.x >= m_items.size() || position.y >= m_items[0].size() || position.x < 0 || position.y < 0)
	{
		throw std::invalid_argument("Invalid position");
	}
	return m_items[position.x][position.y];
}

void Inventory::printInventory() const {
	for (auto row : m_items)
	{
		for (auto item : row)
		{
			if (item == nullptr)
			{
				std::cout << "NULL ";
			}
			else
			{
				std::cout << item->getType() << " ";
			}
		}
		std::cout << std::endl;
	}
}