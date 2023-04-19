#pragma once

#include <SFML/Graphics.hpp>

#include "Camera.h"
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

    void draw();

    void activateBuildMode();

    void deactivateBuildMode();

private:
    sf::RenderWindow& m_window;
    Type m_screenType;

    std::shared_ptr<Camera> m_camera;
    // TODO - handle several boards
    std::shared_ptr<Board> m_board;
    std::shared_ptr<EntityManager> m_entityManager;
    std::shared_ptr<Character> m_player;
    std::shared_ptr<Inventory> m_inventory;

    bool m_buildMode = false;
    std::shared_ptr<Building> m_currentBuilding;
};


