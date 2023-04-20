#pragma once

// STD
#include <map>
#include <string>
#include <memory>

class Board;

class BoardManager
{
public:
	BoardManager();
	~BoardManager();
	void addBoard(std::string name, std::shared_ptr<Board> board);
	std::shared_ptr<Board> getBoard(std::string name);

private:
	std::map<std::string, std::shared_ptr<Board>> m_boards;
};

