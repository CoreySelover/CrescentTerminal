#pragma once

#include <SFML/Graphics.hpp>

#include "Camera.h"
#include "BoardManager.h"
#include "Board.h"
#include "EntityManager.h"
#include "Character.h"
#include "GUIManager.h"
#include "Building.h"
#include "Inventory.h"

struct TimeDate {
	int m_hour;
	int m_minute;
	int m_date;
	int m_month;
	int m_year;
};

class Game {
public:
    Game(sf::RenderWindow& window);

    ~Game();

    void startGame(std::string filePath);

    void handleInput(sf::Event event);

    void update(sf::Time deltaTime);

    void updateTimeAndDate(sf::Time deltaTime);

    int getDaysInMonth(int month, int year);
    
    void handleCollisions();

    void fadeIn(float duration = 1.0f);

    void fadeOut(float duration = 1.0f);

    void draw();

    void drawEntities();

    void activateBuildMode();

    void deactivateBuildMode();

    // Data
    void saveData(std::string fileName = "NEW_GAME");

    void loadData(std::string fileName = "NEW_GAME");

    // Getters
    TimeDate getTimeDate() const;

private:
    sf::RenderWindow& m_window;
    sf::RectangleShape m_fadeRect;

    std::shared_ptr<Camera> m_camera;
    std::shared_ptr<Board> m_currentBoard;
    std::shared_ptr<EntityManager> m_entityManager;
    std::shared_ptr<Character> m_player;
    std::shared_ptr<Inventory> m_inventory;

    bool m_buildMode = false;
    std::shared_ptr<Building> m_currentBuilding;

    TimeDate m_timeDate;
};


