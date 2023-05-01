#pragma once

#include <SFML/Graphics.hpp>

#include "Camera.h"
#include "BoardManager.h"
#include "Board.h"
#include "EntityManager.h"
#include "Character.h"
#include "Building.h"
#include "Inventory.h"

class Game {
public:
    Game(sf::RenderWindow& window);

    ~Game();

    enum class Type {
        MainMenu,
        GameWorld
    };

    void setScreenType(Type type);

    void handleInput(sf::Event event);

    void update(sf::Time deltaTime);
    
    void handleCollisions();

    void fadeIn(float duration = 1.0f);

    void fadeOut(float duration = 1.0f);

    void draw();

    void drawEntities();

    void activateBuildMode();

    void deactivateBuildMode();

    void saveGame(std::string fileName = "NEW_GAME");

    void loadGame(std::string fileName = "NEW_GAME");

private:
    sf::RenderWindow& m_window;
    Type m_screenType;
    sf::RectangleShape m_fadeRect;

    std::shared_ptr<Camera> m_camera;
    std::shared_ptr<Board> m_currentBoard;
    std::shared_ptr<EntityManager> m_entityManager;
    std::shared_ptr<Character> m_player;
    std::shared_ptr<Inventory> m_inventory;

    bool m_buildMode = false;
    std::shared_ptr<Building> m_currentBuilding;
};


