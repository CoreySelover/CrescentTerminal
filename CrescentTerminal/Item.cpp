#include "Item.h"

Item::Item(ItemType type, std::string boardName, sf::Vector2i initPos, bool isStackable, int stackSize) : m_isStackable(isStackable), m_stackSize(stackSize), m_boardName(boardName), m_type(type)
{
	if (boardName.compare("INVENTORY") == 0) {
		m_inInventory = true;
		m_worldPosition = sf::Vector2i(-1, -1);
		m_inventoryPosition = initPos;
	}
	else {
		m_inInventory = false;
		m_worldPosition = initPos;
		m_inventoryPosition = sf::Vector2i(-1, -1);
	}
}

Item::~Item()
{
}

void Item::changeStackSize(int delta) {
	m_stackSize += delta;
}

void Item::setInventoryPosition(sf::Vector2i position) {
	m_inventoryPosition = position;
	if (m_inventoryPosition.x >= 0 && m_inventoryPosition.y >= 0) {
		m_inInventory = true;
	}
	else {
		m_inInventory = false;
	}
}
