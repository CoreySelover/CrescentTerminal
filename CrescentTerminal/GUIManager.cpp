#include "GUIManager.h"
#include "TextureManager.h"
#include "Global.h"

#include <iostream>

GUIElement::GUIElement(std::string name, std::string filePath) : m_name(name)
{
    m_sprite.setTexture(TextureManager::getTexture(filePath));
    m_sprite.setScale(GUI_SCALE, GUI_SCALE);
}

void GUIElement::draw(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}

void GUIElement::handleEvent(const sf::Event& event)
{
    if (event.type == sf::Event::MouseButtonPressed)
    {
        sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
        if (m_sprite.getGlobalBounds().contains(mousePos))
        {
            // Handle click event
            std::cout << m_name << " clicked!" << std::endl;
        }
    }
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

void GUIManager::handleInput(const sf::Event& event)
{
    for (auto& element : m_elements)
    {
		element.second->handleEvent(event);
	}
}

