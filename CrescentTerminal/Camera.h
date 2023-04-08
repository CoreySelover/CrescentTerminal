#pragma once

#include <SFML/Graphics.hpp>

class Camera {
public:
    Camera(sf::RenderWindow& window, sf::Vector2f target = sf::Vector2f(0, 0))
        : m_window(window)
        , m_target(target)
        , m_view(window.getDefaultView())
    {
        m_view.zoom(0.25f);
    }

    void update(sf::Time dt) {
        m_view.setCenter(m_target);
        m_window.setView(m_view);
    }

    void setTarget(sf::Vector2f target) {
        m_target = target;
    }

private:
    sf::RenderWindow& m_window;
    sf::Vector2f m_target;
    sf::View m_view;
};
