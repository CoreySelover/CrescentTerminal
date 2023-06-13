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
	Item(ItemType type, std::string boardName, sf::Vector2i initPos, bool isStackable = true, int stackSize = 1);
	~Item();
	void changeStackSize(int delta);

protected:
	bool m_inInventory;
	bool m_isStackable;
	int m_stackSize;

	sf::Vector2i m_worldPosition;
	std::string m_boardName;

	ItemType m_type;

};

