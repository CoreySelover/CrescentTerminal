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

    enum class ScreenType {
        MainMenu,
        GameWorld
    };

    ScreenType currentScreen = ScreenType::GameWorld;
    game.startGame("NEW_GAME");

    while (window.isOpen()) {
        sf::Time deltaTime = GAME_CLOCK.restart();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else {
                if (currentScreen == ScreenType::MainMenu) {
					// Handle main menu input
				}
                else if (currentScreen == ScreenType::GameWorld) {
					// Handle game world input
                    game.handleInput(event);
				}
                
            }
        }

        if (currentScreen == ScreenType::MainMenu) {

        }
        else if (currentScreen == ScreenType::GameWorld) {
            game.update(deltaTime);
            game.draw();
		}
    }

    return 0;
}
