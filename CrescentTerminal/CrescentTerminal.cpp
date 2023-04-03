// STD
#include <iostream>;

// SFML
#include <SFML/Graphics.hpp>

// Crescent Terminal
#include "EntityManager.h"

int main()
{
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(desktop, "Crescent Terminal");
    EntityManager entityManager;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.display();
    }

    return 0;
}