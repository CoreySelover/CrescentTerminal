#pragma once

#include <string>
#include <vector>
#include <memory>

class Item;

class Inventory
{
public:
	static Inventory& getInstance()
	{
		static Inventory instance;
		return instance;
	}

	void addResource(std::string resource, int amount);
	void removeResource(std::string resource, int amount);
	void addResources(std::vector<std::pair<std::string, int>> resources);
	void removeResources(std::vector<std::pair<std::string, int>> resources);

	// Getting the amount of a resource
	int getAmountOf(std::string resource) const;
	bool doWeHaveEnough(std::string resource, int amount) const;
	bool doWeHaveEnough(std::vector<std::pair<std::string, int>> requirements) const;

private:
	Inventory(); // Private constructor

	int m_steel;
	int m_plastic;
	int m_glass;

	std::vector<std::vector<std::shared_ptr<Item>>> m_items;
};
