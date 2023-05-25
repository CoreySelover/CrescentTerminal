#pragma once

#include <SFML/Graphics.hpp>
#include <map>

class GUIElement
{
public:
    GUIElement(std::string name, std::string filePath);
    virtual void update() {}
    virtual void draw(sf::RenderWindow& window);
    virtual bool handleInput(const sf::Event& event);
    void setPosition(sf::Vector2f position) { m_sprite.setPosition(position); }

private:
    std::string m_name;
    sf::Sprite m_sprite;
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

