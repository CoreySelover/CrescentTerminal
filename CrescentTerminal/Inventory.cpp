#include "Inventory.h"

#include <stdexcept>

Inventory::Inventory()
{
	// TODO - read from file
	m_steel = 50;
	m_plastic = 50;
	m_glass = 100;
}

Inventory::~Inventory()
{
}

int Inventory::getAmountOf(std::string resource) const {
	if (resource == "steel") { return m_steel; }
	else if (resource == "plastic") { return m_plastic; }
	else if (resource == "glass") { return m_glass; }
	
	throw std::invalid_argument("Invalid resource name");
}