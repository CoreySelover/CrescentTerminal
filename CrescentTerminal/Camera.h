#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>

#include "Global.h"

class Camera {
public:
    Camera(sf::RenderWindow& window, sf::Vector2f target = sf::Vector2f(0, 0));

    void setBoardSize(sf::Vector2f boardSize);

    void update(sf::Time dt);

    void setTarget(sf::Vector2f target);

    void pan(Direction direction);

    void zoom(float zoom);

private:
    sf::RenderWindow& m_window;
    sf::Vector2f m_target;
    float m_speed;
    sf::View m_view;
    sf::Vector2f m_boardSize;
};
