// STD
#include <iostream>

// SFML
#include <SFML/Graphics.hpp>

// Crescent Terminal
#include "Global.h"
#include "Game.h"

int main()
{
    // Pre-game loading
    if (!FONT.loadFromFile("Assets/Fonts/arial.ttf")) throw std::runtime_error("Could not load font");

    // Window setup
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Crescent Terminal");
    //sf::RenderWindow window(sf::VideoMode(800, 600), "Crescent Terminal");
    RESOLUTION = window.getSize();
    window.setFramerateLimit(60);

    // Game setup
    enum class ScreenType {
        MainMenu,
        GameWorld
    };
    ScreenType currentScreen = ScreenType::GameWorld;
    Game game(window);
    game.startGame("NEW_GAME");

    while (window.isOpen()) {
        sf::Time deltaTime = GAME_CLOCK.restart();

        sf::Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed) {
				window.close();
            }
            if (currentScreen == ScreenType::MainMenu) {
				// Handle main menu input
			}
            else if (currentScreen == ScreenType::GameWorld) {
				// Handle game world input
                game.handleInput(event);
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
