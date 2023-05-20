
#include <sstream>
#include <iostream>

#include "pugixml.hpp"

#include "Game.h"
#include "EntityManager.h"
#include "Character.h"
#include "Board.h"
#include "Camera.h"
#include "Building.h"

Game::Game(sf::RenderWindow& window) : m_window(window)
{
}

Game::~Game()
{
}

void Game::startGame(std::string filePath)
{
    // Map
    BoardManager::getInstance().addBoard("World", std::make_shared<Board>("World", "Assets/Maps/World.xml"));
    m_currentBoard = BoardManager::getInstance().getBoard("World");
    m_currentBoard->buildBuilding(BuildingType_Base, tileCoordsToPixels(25,11));

    // Camera
    m_camera = std::make_shared<Camera>(m_window);
    m_camera->setBoardSize(m_currentBoard->getBoardSizeInPixels());
    m_fadeRect.setSize(sf::Vector2f(m_window.getSize()));
    m_fadeRect.setFillColor(sf::Color::Black);

    // Entities
    m_entityManager = std::make_shared<EntityManager>();
    m_entityManager->addEntity(std::make_shared<Character>("Player", m_currentBoard));
    m_player = std::static_pointer_cast<Character>(m_entityManager->getEntity("Player"));
    m_player->setPosition(tileCoordsToPixels(m_currentBoard->getEntrances()["main"]));

    // Build Mode
    m_currentBuilding = std::make_shared<Building>(BuildingType::BuildingType_Base, m_currentBoard->getName());

    // Inventory
    m_inventory = std::make_shared<Inventory>();
}

void Game::handleInput(sf::Event event)
{
    if (!USER_HAS_CONTROL) return;
    if (event.type == sf::Event::KeyPressed)
    {
        // DEBUG - TURN THESE OFF FOR RELEASE
        if (event.key.code == sf::Keyboard::H) {
            saveData();
		}
        if (event.key.code == sf::Keyboard::J) {
			loadData("Saves/test.txt");
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

void Game::update(sf::Time deltaTime)
{
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

    // Draw game world
    m_currentBoard->drawBackground(m_window);
    m_currentBoard->drawShadows(m_window);
    m_currentBoard->drawObstacles(m_window);
    m_entityManager->drawEntities(m_window);
    m_currentBoard->drawForeground(m_window);
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

void Game::saveData(std::string fileName) 
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

    pugi::xml_document doc;
    pugi::xml_node root = doc.append_child("save");

    // Create the player node and add its attributes
    pugi::xml_node playerNode = root.append_child("player");
    playerNode.append_attribute("posX").set_value(m_player->getPosition().x);
    playerNode.append_attribute("posY").set_value(m_player->getPosition().x);

    // Create the boards node and add each map as a child node
    pugi::xml_node boardsNode = root.append_child("boards");
    
    for (auto &board : BoardManager::getInstance().getBoards()) {
        // Create the map node and add its attributes
        pugi::xml_node boardNode = boardsNode.append_child("board");
        boardNode.append_attribute("name").set_value(board.second->getName().c_str());
        boardNode.append_attribute("file").set_value(board.second->getFileName().c_str());

        // Create the buildings node and add each building as a child node
        pugi::xml_node buildingsNode = boardNode.append_child("buildings");
        for (auto &building : board.second->getBuildings()) {
            // Create the building node and add its attributes
            pugi::xml_node buildingNode = buildingsNode.append_child("building");
            buildingNode.append_attribute("type").set_value(building->getBuildingType());
            buildingNode.append_attribute("x").set_value(building->getBoardPosition().x);
            buildingNode.append_attribute("y").set_value(building->getBoardPosition().y);
        }
    }

    // Save the document to a file
    doc.save_file(fileName.c_str());
}

void Game::loadData(std::string fileName) 
{
    // Load the game using pugixml
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(fileName.c_str());
    if (!result) {
		throw std::runtime_error("Failed to load save file " + fileName);
	}

    // Get the root node
	pugi::xml_node root = doc.child("save");

	// Get the player node and set the player's position
	pugi::xml_node playerNode = root.child("player");
	m_player->setPosition(sf::Vector2f(playerNode.attribute("posX").as_float(), playerNode.attribute("posY").as_float()));

	// Get the boards node and load each board
	pugi::xml_node boardsNode = root.child("boards");
    for (pugi::xml_node boardNode = boardsNode.child("board"); boardNode; boardNode = boardNode.next_sibling("board")) {
		std::string boardName = boardNode.attribute("name").as_string();
        std::string fileName = boardNode.attribute("file").as_string();
		std::shared_ptr<Board> board = BoardManager::getInstance().getBoard(boardName);
        if (board == nullptr) {
            BoardManager::getInstance().addBoard(boardName, std::make_shared<Board>(boardName, fileName));
		}

		// Get the buildings node and load each building
		pugi::xml_node buildingsNode = boardNode.child("buildings");
        for (pugi::xml_node buildingNode = buildingsNode.child("building"); buildingNode; buildingNode = buildingNode.next_sibling("building")) 
        {
			BuildingType buildingType = static_cast<BuildingType>(buildingNode.attribute("type").as_int());
			sf::Vector2i buildingPos = sf::Vector2i(buildingNode.attribute("x").as_int(), buildingNode.attribute("y").as_int());

			BoardManager::getInstance().getBoard(boardName)->buildBuilding(buildingType, tileCoordsToPixels(buildingPos));
		}
	}
}
