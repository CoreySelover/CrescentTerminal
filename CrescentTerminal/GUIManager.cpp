#include "GUIManager.h"
#include "TextureManager.h"
#include "Global.h"

#include <iostream>

// GUIElement
GUIElement::GUIElement(std::string name, std::string filePath) : m_name(name)
{
    m_sprite.setTexture(TextureManager::getTexture(filePath));
    m_sprite.setScale(GUI_SCALE, GUI_SCALE);
}

void GUIElement::draw(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}

bool GUIElement::handleInput(const sf::Event& event)
{
    if (event.type == sf::Event::MouseButtonPressed)
    {
        sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
        if (m_sprite.getGlobalBounds().contains(mousePos))
        {
            // Handle click event
            std::cout << m_name << " clicked!" << std::endl;
            return true;
        }
    }

    return false;
}

// TimeWeather
TimeWeather::TimeWeather(std::string name, std::string filePath) : GUIElement(name, filePath)
{
	m_weather.setFont(FONT);
	m_weather.setCharacterSize(12 * GUI_SCALE);
	m_weather.setFillColor(sf::Color::White);
	m_weather.setPosition(sf::Vector2f(25, 12) * GUI_SCALE);

	m_date.setFont(FONT);
	m_date.setCharacterSize(12 * GUI_SCALE);
	m_date.setFillColor(sf::Color::White);
	m_date.setPosition(sf::Vector2f(25, 27) * GUI_SCALE);

	m_time.setFont(FONT);
	m_time.setCharacterSize(12 * GUI_SCALE);
	m_time.setFillColor(sf::Color::White);
	m_time.setPosition(sf::Vector2f(25, 42) * GUI_SCALE);

	m_funds.setFont(FONT);
	m_funds.setCharacterSize(12 * GUI_SCALE);
	m_funds.setFillColor(sf::Color::White);
	m_funds.setPosition(sf::Vector2f(25, 57) * GUI_SCALE);
}

void TimeWeather::update() {
	GUIElement::update();
	m_time.setString("12:52");
	m_weather.setString("Sunny");
	m_date.setString("5/25/2023");
	m_funds.setString("1,000,000");
}

void TimeWeather::draw(sf::RenderWindow& window) {
	GUIElement::draw(window);
	window.draw(m_time);
	window.draw(m_date);
	window.draw(m_weather);
	window.draw(m_funds);
}

// GUIManager
GUIManager::GUIManager()
{
}

GUIManager::~GUIManager()
{
	m_elements.clear();
}

void GUIManager::addElement(std::string name, std::shared_ptr<GUIElement> element)
{
	m_elements[name] = element;
}

std::shared_ptr<GUIElement> GUIManager::getElement(std::string name)
{
	return m_elements[name];
}

void GUIManager::update()
{
    for (auto& element : m_elements)
    {
		element.second->update();
	}
}

void GUIManager::draw(sf::RenderWindow& window)
{
    for (auto& element : m_elements)
    {
		element.second->draw(window);
	}
}

bool GUIManager::handleInput(const sf::Event& event)
{
    for (auto& element : m_elements)
    {
        if (element.second->handleInput(event))
        {
			return true;
		}
	}

    return false;
}

