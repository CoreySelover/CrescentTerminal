#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>

class Camera {
public:
    Camera(sf::RenderWindow& window, sf::Vector2f target = sf::Vector2f(0, 0));

    void setBoardSize(sf::Vector2f boardSize);

    void update(sf::Time dt);

    void setTarget(sf::Vector2f target);

private:
    sf::RenderWindow& m_window;
    sf::Vector2f m_target;
    float m_speed;
    sf::View m_view;
    sf::Vector2f m_boardSize;
};
