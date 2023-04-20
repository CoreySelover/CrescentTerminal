#include "BoardManager.h"
#include "Board.h"

BoardManager::BoardManager()
{
}

BoardManager::~BoardManager()
{
}

void BoardManager::addBoard(std::string name, std::shared_ptr<Board> board)
{
	m_boards[name] = board;
}

std::shared_ptr<Board> BoardManager::getBoard(std::string name)
{
	return m_boards[name];
}


