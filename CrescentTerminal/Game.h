#pragma once

#include <SFML/Graphics.hpp>

#include "Camera.h"
#include "Board.h"
#include "EntityManager.h"
#include "Character.h"

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

private:
    sf::RenderWindow& m_window;
    Type m_screenType;

    std::shared_ptr<Camera> m_camera;
    // TODO - handle several boards
    std::shared_ptr<Board> m_board;
    std::shared_ptr<EntityManager> m_entityManager;
    std::shared_ptr<Character> m_player;
};


