// STD
#include <iostream>

// SFML
#include <SFML/Graphics.hpp>

// Crescent Terminal
#include "Global.h"
#include "Game.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Crescent Terminal");
    //sf::RenderWindow window(sf::VideoMode(800, 600), "Crescent Terminal");
    window.setFramerateLimit(60);
    Game game(window);

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Time deltaTime = clock.restart();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else {
                game.handleInput(event);
            }
        }

        game.update(deltaTime);
        game.draw();
    }

    return 0;
}
