#pragma once

// STD
#include <map>
#include <string>
#include <memory>

class Board;
class Blueprint;

class BoardManager
{
public:
    static BoardManager& getInstance()
    {
        static BoardManager instance;
        return instance;
    }

    ~BoardManager();

    BoardManager(const BoardManager&) = delete;
    BoardManager& operator=(const BoardManager&) = delete;

    void addBoard(std::string name, std::shared_ptr<Board> board);
    std::shared_ptr<Board> getBoard(std::string name);
 
    void loadBlueprints();
    std::shared_ptr<Blueprint> getBlueprint(std::string name);

    std::map<std::string, std::shared_ptr<Board>> getBoards() { return m_boards; }

private:
    BoardManager();

    std::map<std::string, std::shared_ptr<Board>> m_boards;
    std::map<std::string, std::shared_ptr<Blueprint>> m_blueprints;
};

