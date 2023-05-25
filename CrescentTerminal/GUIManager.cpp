#include "GUIManager.h"
#include "TextureManager.h"
#include "Global.h"
#include "Game.h"

#include <iostream>

// GUIElement
GUIElement::GUIElement(std::string name, std::string filePath, sf::Vector2f position) : m_name(name)
{
	m_sprite.setTexture(TextureManager::getTexture(filePath));
	m_sprite.setScale(GUI_SCALE, GUI_SCALE);
	setPosition(position);
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

void GUIElement::setPosition(sf::Vector2f position) {
	m_sprite.setPosition(position);
}

// TimeWeather
TimeWeather::TimeWeather(std::string name, std::string filePath, sf::Vector2f position, TimeDate& timeDate) : GUIElement(name, filePath, position), m_timeDate(timeDate)
{
	m_weather.setFont(FONT);
	m_weather.setCharacterSize(10 * GUI_SCALE);
	m_weather.setFillColor(sf::Color::White);

	m_date.setFont(FONT);
	m_date.setCharacterSize(10 * GUI_SCALE);
	m_date.setFillColor(sf::Color::White);

	m_time.setFont(FONT);
	m_time.setCharacterSize(10 * GUI_SCALE);
	m_time.setFillColor(sf::Color::White);

	m_funds.setFont(FONT);
	m_funds.setCharacterSize(10 * GUI_SCALE);
	m_funds.setFillColor(sf::Color::White);

	setPosition(position);
}

void TimeWeather::update() {
	GUIElement::update();

	// Format time
	std::string formattedHour = std::to_string(m_timeDate.m_hour);
	if (formattedHour.length() == 1)
		formattedHour.insert(0, "0");
	std::string formattedMinute = std::to_string(m_timeDate.m_minute);
	if (formattedMinute.length() == 1)
		formattedMinute.insert(0, "0");
	m_time.setString(formattedHour + ":" + formattedMinute);

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

void TimeWeather::setPosition(sf::Vector2f position) {
	GUIElement::setPosition(position);
	m_weather.setPosition(m_sprite.getPosition() + (sf::Vector2f(15, 4) * GUI_SCALE));
	m_date.setPosition(m_sprite.getPosition() + (sf::Vector2f(15, 19) * GUI_SCALE));
	m_time.setPosition(m_sprite.getPosition() + (sf::Vector2f(15, 34) * GUI_SCALE));
	m_funds.setPosition(m_sprite.getPosition() + (sf::Vector2f(15, 49) * GUI_SCALE));
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

