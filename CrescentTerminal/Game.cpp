
#include <sstream>
#include <iostream>
#include <fstream>

#include "Game.h"
#include "EntityManager.h"
#include "Character.h"
#include "Board.h"
#include "Camera.h"
#include "Building.h"

Game::Game(sf::RenderWindow& window) : m_window(window)
{
    // Meta
    m_screenType = Type::GameWorld;

    // Map
    BoardManager::getInstance().addBoard("World", std::make_shared<Board>("World", "Assets/Maps/World.xml"));
    m_currentBoard = BoardManager::getInstance().getBoard("World");

    // Camera
    m_camera = std::make_shared<Camera>(window);
    m_camera->setBoardSize(m_currentBoard->getBoardSizeInPixels());
    m_fadeRect.setSize(sf::Vector2f(m_window.getSize()));
    m_fadeRect.setFillColor(sf::Color::Black);

    // Entities
    m_entityManager = std::make_shared<EntityManager>();
    m_entityManager->addEntity(std::make_shared<Character>("Player", m_currentBoard));
    m_player = std::static_pointer_cast<Character>(m_entityManager->getEntity("Player"));
    
    // Build Mode
    m_currentBuilding = std::make_shared<Building>(BuildingType::BuildingType_Base, m_currentBoard->getName());

    // Inventory
    m_inventory = std::make_shared<Inventory>();
}

Game::~Game()
{
}

void Game::setScreenType(Type type) 
{
    switch (type) {
    case Type::MainMenu:
        // Set up main menu
        break;
    case Type::GameWorld:
        // Set up game world
        break;
    }
    m_screenType = type;
}

void Game::handleInput(sf::Event event)
{
    // Handle input for the current screen type
    if (m_screenType == Type::MainMenu) {
        // Handle input for main menu
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Escape) {
				setScreenType(Type::GameWorld);
			}
		}
    }
    else if (m_screenType == Type::GameWorld) {
        if (!USER_HAS_CONTROL) return;
        if (event.type == sf::Event::KeyPressed)
        {
            // DEBUG - TURN THESE OFF FOR RELEASE
            if (event.key.code == sf::Keyboard::H) {
                saveGame();
			}
            if (event.key.code == sf::Keyboard::J) {
				loadGame();
            }
            // Normal character movement
            if (!m_buildMode) {
                switch (event.key.code) {
                case sf::Keyboard::W:
                    m_player->walk(Direction::UP);
                    break;
                case sf::Keyboard::S:
                    m_player->walk(Direction::DOWN);
                    break;
                case sf::Keyboard::A:
                    m_player->walk(Direction::LEFT);
                    break;
                case sf::Keyboard::D:
                    m_player->walk(Direction::RIGHT);
                    break;
                case sf::Keyboard::B:
                    activateBuildMode();
                    break;
                default:
                    break;
                }
            }
            // Build mode
            else if (m_buildMode) {
                switch (event.key.code) {
				case sf::Keyboard::B:
					deactivateBuildMode();
					break;
                case sf::Keyboard::Num1:
                    m_currentBuilding = std::make_shared<Building>(BuildingType::BuildingType_Base, m_currentBoard->getName());
					break;
                case sf::Keyboard::Num2:
                    m_currentBuilding = std::make_shared<Building>(BuildingType::BuildingType_Shed, m_currentBoard->getName());
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
            case sf::Keyboard::Escape:
                m_screenType = Type::MainMenu;
            default:
                break;
            }
        }
        if (event.type == sf::Event::KeyReleased)
        {
            if (USER_HAS_CONTROL) {
                switch (event.key.code) {
                case sf::Keyboard::W:
                    m_player->stopWalking(Direction::UP);
                    break;
                case sf::Keyboard::S:
                    m_player->stopWalking(Direction::DOWN);
                    break;
                case sf::Keyboard::A:
                    m_player->stopWalking(Direction::LEFT);
                    break;
                case sf::Keyboard::D:
                    m_player->stopWalking(Direction::RIGHT);
                    break;
                default:
                    break;
                }
            }
            // Put other key releases here that should be allowed
            // even if the user doesn't have control
        }
        if (event.type == sf::Event::MouseButtonPressed)
        {
            // Commenting because this is hard to read
            if (m_buildMode) {
                if (event.mouseButton.button == sf::Mouse::Left) {
					sf::Vector2f mousePos = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));

                    // Check if we meet the requirements to build
                    // and if the proposed tiles are valid
                    if (m_inventory->doWeHaveEnough(m_currentBuilding->getCost())
                        && m_currentBoard->canBuildHere(m_currentBuilding->getFootprintSize(), mousePos, m_currentBuilding->getBuildBuffer()))
                    {
                        // Build the building
                        m_currentBoard->buildBuilding(m_currentBuilding->getBuildingType(), mousePos);

                        // If the building has an interior, add it to the board manager
                        if (m_currentBoard->lastBuilding()->getInterior() != nullptr) 
                        {
                            BoardManager::getInstance().addBoard(m_currentBoard->lastBuilding()->getInterior()->getName(), m_currentBoard->lastBuilding()->getInterior());
                        }

                        // Remove the resources from the inventory
						m_inventory->removeResources(m_currentBuilding->getCost());
					}
				}
			}
		}
    }
}

void Game::update(sf::Time deltaTime)
{
	// Update the current screen type
    if (m_screenType == Type::MainMenu) {
		// Update main menu
	}
    else if (m_screenType == Type::GameWorld) {
        // Normal character movement
        if (!m_buildMode) {
            m_entityManager->update(deltaTime.asMilliseconds());
            handleCollisions();
            m_camera->setTarget(m_player->getPosition());
        }

        m_camera->update(deltaTime);

        // Build mode
        if (m_buildMode) {
			sf::Vector2f mousePos = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));
			m_camera->setTarget(mousePos);

            // Highlight the tiles that the building will occupy
            bool canBuild = m_inventory->doWeHaveEnough(m_currentBuilding->getCost())
                && m_currentBoard->canBuildHere(m_currentBuilding->getFootprintSize(), mousePos, m_currentBuilding->getBuildBuffer());
            m_currentBoard->highlightTiles(m_currentBuilding->getFootprintSize(), mousePos, canBuild);
		}
	}
}

void Game::handleCollisions() {

    sf::Vector2i currentTile = pixelsToTileCoords(m_player->getPosition());
    if (!m_currentBoard->isTileInBounds(currentTile.x, currentTile.y)) return;

    // Doors
    if (m_currentBoard->isDoor(currentTile)) {
        std::string newBoardName = m_currentBoard->getDoorDestinationName(currentTile);
        sf::Vector2i newBoardStartPos = m_currentBoard->getDoorDestinationStartPos(currentTile);
        
        std::shared_ptr<Board> newBoard = BoardManager::getInstance().getBoard(newBoardName);
        if (newBoard == nullptr) {
			throw std::runtime_error("Board " + newBoardName + " does not exist");
		}

        USER_HAS_CONTROL = false;
        fadeOut();

        m_player->setBoard(newBoard);
        m_camera->setBoardSize(newBoard->getBoardSizeInPixels());
        m_player->setPosition(tileCoordsToPixels(newBoardStartPos));
        m_camera->setPosition(m_player->getPosition());
        m_currentBoard = newBoard;

        fadeIn();
        GAME_CLOCK.restart();
        USER_HAS_CONTROL = true;
    }
}

void Game::fadeOut(float duration) {
    sf::Clock clock;
    while (clock.getElapsedTime().asSeconds() < duration) {
        m_window.clear();
        m_fadeRect.setFillColor(sf::Color(0, 0, 0, 255 * (clock.getElapsedTime().asSeconds() / duration)));
        drawEntities();
        m_window.draw(m_fadeRect);
		m_window.display();
	}
}

void Game::fadeIn(float duration) {
    sf::Clock clock;
    while (clock.getElapsedTime().asSeconds() < duration) {
        m_window.clear();
        m_fadeRect.setFillColor(sf::Color(0, 0, 0, 255 * (1 - (clock.getElapsedTime().asSeconds() / duration))));
        drawEntities();
        m_window.draw(m_fadeRect);
        m_window.display();
    }
}

void Game::draw()
{
    m_window.clear();

    drawEntities();

    m_window.display();
}

void Game::drawEntities() {
    // Draw the current screen type
    if (m_screenType == Type::MainMenu) {
        // Draw main menu
    }
    else if (m_screenType == Type::GameWorld) {
        // Draw game world
        m_currentBoard->drawBackground(m_window);
        m_currentBoard->drawObstacles(m_window);
        m_entityManager->drawEntities(m_window);
        m_currentBoard->drawForeground(m_window);
    }
}

void Game::activateBuildMode()
{
    m_buildMode = true;
    m_player->stopCompletely();
    
    m_camera->zoom(1.6f);
}

void Game::deactivateBuildMode()
{
	m_buildMode = false;
    m_currentBoard->clearHighlights();

    m_camera->zoom(0.625f);
}

void Game::saveGame(std::string fileName) 
{
    if (fileName == "NEW_GAME") {
        // Since this is a new game, create a file name based on the current time
        time_t rawtime;
        struct tm timeinfo;
        char buffer[80];

        time(&rawtime);
        localtime_s(&timeinfo, &rawtime);

        strftime(buffer, sizeof(buffer), "%Y-%m-%d_%H-%M-%S", &timeinfo);
        fileName = std::string(buffer);
        fileName += ".txt";
        fileName.insert(0, "Saves/");
    }

    std::ofstream outFile;
    outFile.open(fileName);

    if (outFile.is_open()) {

        // Player data
        outFile << "---Player Data---" << std::endl;
        outFile << "pp:" << m_player->getPosition().x << "," << m_player->getPosition().y << "\n" << std::endl;

        // Board data
        outFile << "---Board Data---" << std::endl << BoardManager::getInstance().boardData() << std::endl;

        outFile.close();
    }
    else {
        std::cout << "Unable to open file: " << fileName << std::endl;
    }
}

void Game::loadGame(std::string fileName) 
{

}

