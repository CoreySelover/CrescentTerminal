// STD
#include <iostream>

// SFML
#include <SFML/Graphics.hpp>

// Crescent Terminal
#include "EntityManager.h"
#include "Character.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Crescent Terminal");

    EntityManager entityManager;
    entityManager.addEntity(std::make_shared<Character>("Player", sf::Vector2f(), true));
    entityManager.getEntity("Player")->loadTexture("Assets/Player.png");

    auto player = std::static_pointer_cast<Character>(entityManager.getEntity("Player"));

    // TODO - move these variables into a GameVariables class or something
    bool userHasControl = true;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed)
            {
                if (userHasControl) {
                    switch (event.key.code) {
                    case sf::Keyboard::W:
                        player->movePosition(sf::Vector2f(0, -5));
                        break;
                    case sf::Keyboard::S:
                        player->movePosition(sf::Vector2f(0, 5));
                        break;
                    case sf::Keyboard::A:
                        player->movePosition(sf::Vector2f(-5, 0));
                        break;
                    case sf::Keyboard::D:
                        player->movePosition(sf::Vector2f(5, 0));
                        break;
                    }
                }
                else { // In case e.g. we want user to be able to quit during a cutscene
                    
                }
			}
        }

        window.clear();
        entityManager.update();
        entityManager.drawEntities(window);
        window.display();
    }

    return 0;
}