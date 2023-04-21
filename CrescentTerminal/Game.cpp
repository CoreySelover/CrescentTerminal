
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
    m_boardManager = std::make_shared<BoardManager>();
    m_boardManager->addBoard("World", std::make_shared<Board>("World", 50, 50));
    m_currentBoard = m_boardManager->getBoard("World");

    // Camera
    m_camera = std::make_shared<Camera>(window);
    m_camera->setBoardSize(m_currentBoard->getBoardSize());

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
        if (event.type == sf::Event::KeyPressed)
        {
            // Normal character movement
            if (USER_HAS_CONTROL && !m_buildMode) {
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
                        && m_currentBoard->canBuildHere(m_currentBuilding->getFootprintSize(), mousePos)) 
                    {
                        // Build the building
                        m_currentBoard->buildBuilding(m_currentBuilding->getBuildingType(), mousePos);

                        // If the building has an interior, add it to the board manager
                        if (m_currentBoard->lastBuilding()->getInterior() != nullptr) 
                        {
                            m_boardManager->addBoard(m_currentBoard->lastBuilding()->getInterior    ()->getName(), m_currentBoard->lastBuilding()->getInterior());
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
                && m_currentBoard->canBuildHere(m_currentBuilding->getFootprintSize(), mousePos);
            m_currentBoard->highlightTiles(m_currentBuilding->getFootprintSize(), mousePos, canBuild);
		}
	}
}

void Game::handleCollisions() {

    sf::Vector2i currentTile = Board::pixelsToTileCoords(m_player->getPosition());
    if (!m_currentBoard->isTileInBounds(currentTile.x, currentTile.y)) return;

    // Doors
    if (m_currentBoard->getTile(currentTile).getType() == TileType_Door) {
        std::string newBoardName = m_currentBoard->getDoorDestinationName(currentTile);
        sf::Vector2i newBoardStartPos = m_currentBoard->getDoorDestinationStartPos(currentTile);
        
        std::shared_ptr<Board> newBoard = m_boardManager->getBoard(newBoardName);
        if (newBoard == nullptr) {
			throw std::runtime_error("Board " + newBoardName + " does not exist");
		}

        fadeOut();
        m_player->setBoard(newBoard);
        m_player->setPosition(Board::tileCoordsToPixels(newBoardStartPos));
        m_currentBoard = newBoard;
        m_camera->setBoardSize(m_currentBoard->getBoardSize());
        m_camera->setPosition(m_player->getPosition());
    }
}

void Game::fadeOut(float duration) {
    sf::RectangleShape fadeRect;
	fadeRect.setSize(sf::Vector2f(m_window.getSize()));
	fadeRect.setFillColor(sf::Color::Black);
	sf::Clock clock;
    while (clock.getElapsedTime().asSeconds() < duration) {
		float alpha = 255 * (clock.getElapsedTime().asSeconds() / duration);
		fadeRect.setFillColor(sf::Color(0, 0, 0, alpha));
		m_window.draw(fadeRect);
		m_window.display();
	}
}

void Game::fadeIn(float duration) {
    sf::RectangleShape fadeRect;
	fadeRect.setSize(sf::Vector2f(m_window.getSize()));
	fadeRect.setFillColor(sf::Color::Black);
	sf::Clock clock;
	while (clock.getElapsedTime().asSeconds() < duration) {
        float alpha = 255 * (1 - clock.getElapsedTime().asSeconds() / duration);
    	fadeRect.setFillColor(sf::Color(0, 0, 0, alpha));
        m_window.draw(fadeRect);
        m_window.display();
    }
}

void Game::draw()
{
    m_window.clear();
    // Draw the current screen type
    if (m_screenType == Type::MainMenu) {
        // Draw main menu
    }
    else if (m_screenType == Type::GameWorld) {
        // Draw game world
        m_currentBoard->drawBackground(m_window);
        m_entityManager->drawEntities(m_window);
        //board.drawForeground(m_window);
    }
    m_window.display();
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

