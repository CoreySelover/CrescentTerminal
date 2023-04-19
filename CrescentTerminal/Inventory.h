#pragma once

#include <string>

class Inventory
{
public:
	Inventory();
	~Inventory();
	int getAmountOf(std::string resource) const;

private:
	int m_steel;
	int m_plastic;
	int m_glass;
};

