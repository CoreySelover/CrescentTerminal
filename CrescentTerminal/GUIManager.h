#pragma once

#include <SFML/Graphics.hpp>
#include <map>

// Base class for all GUI elements
class GUIElement
{
public:
    GUIElement(std::string name, std::string filePath, sf::Vector2f position);
    virtual void update() {}
    virtual void draw(sf::RenderWindow& window);
    virtual bool handleInput(const sf::Event& event);
    virtual void setPosition(sf::Vector2f position);

protected:
    sf::Sprite m_sprite;

private:
    std::string m_name;
};

// Specific GUI elements
class TimeWeather : public GUIElement
{
public:
    TimeWeather(std::string name, std::string filePath, sf::Vector2f position);
    void update();
    void draw(sf::RenderWindow& window);
    void setPosition(sf::Vector2f position);

private:
    sf::Text m_time;
	sf::Text m_weather;
    sf::Text m_date;
    sf::Text m_funds;
};

class GUIManager
{
public:
    static GUIManager& getInstance()
    {
        static GUIManager instance;
        return instance;
    }

    ~GUIManager();

    GUIManager(const GUIManager&) = delete;
    GUIManager& operator=(const GUIManager&) = delete;

    void addElement(std::string name, std::shared_ptr<GUIElement> element);
    std::shared_ptr<GUIElement> getElement(std::string name);

    void update();
    void draw(sf::RenderWindow& window);
    bool handleInput(const sf::Event& event);

private:
    GUIManager();

    std::map<std::string, std::shared_ptr<GUIElement>> m_elements;
};

