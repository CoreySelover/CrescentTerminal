#pragma once

#include <SFML/Graphics.hpp>

enum ItemType {
	ItemType_Seed_Tomato,
	ItemType_Seed_Carrot,
	ItemType_Seed_Potato,
	ItemType_Count
};

class Item
{
public:
	Item(ItemType type, std::string boardName, sf::Vector2i initPos = sf::Vector2i(-1, -1), bool isStackable = true, int stackSize = 1);
	~Item();
	void changeStackSize(int delta);
	void setInventoryPosition(sf::Vector2i inventoryPosition);

	ItemType getType() const { return m_type; }

protected:
	bool m_inInventory;
	bool m_isStackable;
	int m_stackSize;

	sf::Vector2i m_worldPosition;
	sf::Vector2i m_inventoryPosition;
	std::string m_boardName;

	ItemType m_type;

};

