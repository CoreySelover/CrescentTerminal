// STD
#include <iostream>

// SFML
#include <SFML/Graphics.hpp>

// Crescent Terminal
#include "Global.h"
#include "EntityManager.h"
#include "Character.h"
#include "Board.h"
#include "Camera.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Crescent Terminal");
    window.setFramerateLimit(60);
    Camera camera(window);

    Board board(50, 50);
    board.getTile(5, 5).setObstacle(true);

    EntityManager entityManager;
    entityManager.addEntity(std::make_shared<Character>("Player", board));
    auto player = std::static_pointer_cast<Character>(entityManager.getEntity("Player"));

    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Time deltaTime = clock.restart();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed)
            {
                if (USER_HAS_CONTROL) {
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
                    default:
                        break;
                    }
                }
                // Put other key presses here that should be allowed
                // even if the user doesn't have control
                switch (event.key.code) {
                    case sf::Keyboard::F1:
						DEBUG_DRAW = !DEBUG_DRAW;
						break;
                    default:
                        break;
                }
            }
            if (event.type == sf::Event::KeyReleased)
            {
                if (USER_HAS_CONTROL) {
                    switch (event.key.code) {
                    case sf::Keyboard::W:
                        player->stopWalking(Direction::UP);
                        break;
                    case sf::Keyboard::S:
                        player->stopWalking(Direction::DOWN);
                        break;
                    case sf::Keyboard::A:
                        player->stopWalking(Direction::LEFT);
                        break;
                    case sf::Keyboard::D:
                        player->stopWalking(Direction::RIGHT);
                        break;
                    default:
                        break;
                    }
                }
                // Put other key releases here that should be allowed
                // even if the user doesn't have control
            }
        }

        entityManager.update(deltaTime.asMilliseconds());
        camera.setTarget(player->getPosition());
        camera.update(deltaTime);

        window.clear();
        board.drawBackground(window);
        entityManager.drawEntities(window);
        //board.drawForeground(window);
        window.display();
    }

    return 0;
}
