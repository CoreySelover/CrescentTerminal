#pragma once

#include <string>
#include <vector>

class Inventory
{
public:
	Inventory();
	~Inventory();

	void addResource(std::string resource, int amount);
	void removeResource(std::string resource, int amount);
	void addResources(std::vector<std::pair<std::string, int>> resources);
	void removeResources(std::vector<std::pair<std::string, int>> resources);

	// Getting the amount of a resource
	int getAmountOf(std::string resource) const;
	bool doWeHaveEnough(std::string resource, int amount) const;
	bool doWeHaveEnough(std::vector<std::pair<std::string, int>> requirements) const;

private:
	int m_steel;
	int m_plastic;
	int m_glass;
};

