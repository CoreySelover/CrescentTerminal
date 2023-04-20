#include "BoardManager.h"
#include "Board.h"

#include <iostream>

BoardManager::BoardManager()
{
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


