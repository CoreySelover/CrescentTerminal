#pragma once

#include <string>
#include <vector>
#include <memory>

#include <SFML/Graphics.hpp>

class Item;

class Inventory
{
public:
	static Inventory& getInstance()
	{
		static Inventory instance;
		return instance;
	}

	// Resources
	void addResource(std::string resource, int amount);
	void addResources(std::vector<std::pair<std::string, int>> resources);

	void removeResource(std::string resource, int amount);
	void removeResources(std::vector<std::pair<std::string, int>> resources);

	int getAmountOf(std::string resource) const;

	bool doWeHaveEnough(std::string resource, int amount) const;
	bool doWeHaveEnough(std::vector<std::pair<std::string, int>> requirements) const;

	// Items
	bool addItem(std::shared_ptr<Item> item, sf::Vector2i position = sf::Vector2i(-1, -1));
	std::shared_ptr<Item> removeItemAtPosition(sf::Vector2i position);
	std::shared_ptr<Item> getItemAtPosition(sf::Vector2i position) const;

	void printInventory() const;

private:
	Inventory(); // Private constructor
	Inventory(Inventory const&) = delete; // Prevent copy-construction
	void operator=(Inventory const&) = delete; // Prevent assignment
	~Inventory();

	int m_steel;
	int m_plastic;
	int m_glass;

	std::vector<std::vector<std::shared_ptr<Item>>> m_items;
};
