#include "BoardManager.h"
#include "Board.h"
#include "Blueprint.h"

#include <iostream>

BoardManager::BoardManager()
{
	// Load all blueprints
	loadBlueprints();
}

BoardManager::~BoardManager()
{
	// First clear the buildings in all boards
	for (auto& board : m_boards) {
		board.second->clearBuildings();
	}

	m_boards.clear();
}

void BoardManager::addBoard(std::string name, std::shared_ptr<Board> board)
{
	m_boards[name] = board;
}

std::shared_ptr<Board> BoardManager::getBoard(std::string name)
{
	return m_boards[name];
}

void BoardManager::loadBlueprints()
{
	// Load all blueprints
	std::vector<std::string> blueprintNames = { "Base_Blueprint", "Shed_Blueprint"};
	for (auto& name : blueprintNames) {
		m_blueprints[name] = std::make_shared<Blueprint>(name, "Assets/Maps/" + name + ".xml");
	}
}

std::shared_ptr<Blueprint> BoardManager::getBlueprint(std::string name)
{
	return m_blueprints[name];
}

