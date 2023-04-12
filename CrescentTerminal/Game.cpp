
#include "Game.h"
#include "EntityManager.h"
#include "Character.h"
#include "Board.h"
#include "Camera.h"

Game::Game(sf::RenderWindow& window) : m_window(window)
{
    m_screenType = Type::GameWorld;

    m_board = std::make_shared<Board>(50, 50);

    m_camera = std::make_shared<Camera>(window);
    m_camera->setBoardSize(m_board->getBoardSize());

    m_entityManager = std::make_shared<EntityManager>();
    m_entityManager->addEntity(std::make_shared<Character>("Player", m_board));
    m_player = std::static_pointer_cast<Character>(m_entityManager->getEntity("Player"));
}

Game::~Game()
{
    m_camera = nullptr;
    m_board = nullptr;
    m_entityManager = nullptr;
    m_player = nullptr;
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
            if (USER_HAS_CONTROL) {
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
                    if (!m_buildMode)
                        activateBuildMode();
                    else
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
    }
}

void Game::update(sf::Time deltaTime)
{
	// Update the current screen type
    if (m_screenType == Type::MainMenu) {
		// Update main menu
	}
    else if (m_screenType == Type::GameWorld) {
        m_entityManager->update(deltaTime.asMilliseconds());
        m_camera->setTarget(m_player->getPosition());
        m_camera->update(deltaTime);
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
        m_board->drawBackground(m_window);
        m_entityManager->drawEntities(m_window);
        //board.drawForeground(m_window);
    }
    m_window.display();
}

void Game::activateBuildMode()
{
    m_buildMode = true;
}

void Game::deactivateBuildMode()
{
	m_buildMode = false;
}

