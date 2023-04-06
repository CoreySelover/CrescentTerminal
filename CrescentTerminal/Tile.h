#pragma once

#include <SFML/Graphics.hpp>

class Tile {
public:
    Tile(bool isObstacle = false)
        : m_isObstacle(isObstacle)
    {}

    void setObstacle(bool isObstacle) {
        m_isObstacle = isObstacle;
    }

    bool isObstacle() const {
        return m_isObstacle;
    }

    // TODO: Draw sprites instead of rectangles
    void draw(sf::RenderWindow& window, sf::Vector2f position, sf::Vector2f size) const {
        sf::RectangleShape shape(size);
        shape.setPosition(position);
        shape.setFillColor(m_isObstacle ? sf::Color::Black : sf::Color::White);
        shape.setOutlineThickness(1);
        shape.setOutlineColor(sf::Color::Black);
        window.draw(shape);
    }

private:
    bool m_isObstacle;
};


