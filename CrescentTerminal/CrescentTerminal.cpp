// STD
#include <iostream>

// SFML
#include <SFML/Graphics.hpp>

// Crescent Terminal
#include "Global.h"
#include "EntityManager.h"
#include "Character.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Crescent Terminal");

    EntityManager entityManager;
    entityManager.addEntity(std::make_shared<Character>("Player"));
    auto player = std::static_pointer_cast<Character>(entityManager.getEntity("Player"));
    player->loadTexture("Assets/Player.png");

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
                        player->walk(Direction::UP);
                        break;
                    case sf::Keyboard::S:
                        player->walk(Direction::DOWN);
                        break;
                    case sf::Keyboard::A:
                        player->walk(Direction::LEFT);
                        break;
                    case sf::Keyboard::D:
                        player->walk(Direction::RIGHT);
                        break;
                    }
                }
                // Put other key presses here that should be allowed
                // even if the user doesn't have control
			}
            if (event.type == sf::Event::KeyReleased)
            {
                if (userHasControl) {
                    switch (event.key.code) {
					case sf::Keyboard::W:
						player->stopWalking();
						break;
					case sf::Keyboard::S:
						player->stopWalking();
						break;
					case sf::Keyboard::A:
						player->stopWalking();
						break;
					case sf::Keyboard::D:
						player->stopWalking();
						break;
					}
				}
				// Put other key releases here that should be allowed
				// even if the user doesn't have control
			}
        }

        window.clear();
        entityManager.update();
        entityManager.drawEntities(window);
        window.display();
    }

    return 0;
}