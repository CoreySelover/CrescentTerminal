#pragma once
#include <string>
class Entity
{
public:
	Entity(std::string name);
	~Entity();
	std::string getName();

private:
	std::string m_name;
};

