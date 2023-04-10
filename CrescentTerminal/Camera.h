#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>

class Camera {
public:
    Camera(sf::RenderWindow& window, sf::Vector2f target = sf::Vector2f(0, 0))
        : m_window(window)
        , m_target(target)
        , m_speed(5.0f) // adjust as needed
        , m_view(window.getDefaultView())
    {
        m_view.zoom(0.25f);
        m_view.setCenter(0, 0);
    }

    void update(sf::Time dt) {
        sf::Vector2f desiredPos = m_target;

        // smoothly move the camera towards the desired position
        sf::Vector2f diff = desiredPos - m_view.getCenter();
        sf::Vector2f displacement = diff * m_speed * dt.asSeconds();
        float maxDisplacement = 50.0f;
        displacement.x = std::max(std::min(displacement.x, maxDisplacement), -maxDisplacement);
        displacement.y = std::max(std::min(displacement.y, maxDisplacement), -maxDisplacement);
        m_view.move(displacement);

        // set the camera view on the window
        m_window.setView(m_view);
    }

    void setTarget(sf::Vector2f target) {
        m_target = target;
    }

private:
    sf::RenderWindow& m_window;
    sf::Vector2f m_target;
    float m_speed;
    sf::View m_view;
};
