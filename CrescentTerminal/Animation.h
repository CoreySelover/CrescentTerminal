#pragma once

// SFML
#include <SFML/Graphics.hpp>

class Animation
{
public:
    Animation(std::string textureFilePath, int x, int y, int width, int height, int numFrames, float frameDuration);

    void setScale(float scale);

    void update(float deltaTime);

    void setPosition(sf::Vector2f position);

    sf::Vector2f getPosition();

    sf::Vector2f getSize();

    void draw(sf::RenderWindow& window);

private:
    int m_frameWidth;
    int m_frameHeight;
    int m_numFrames;
    float m_frameDuration;

    std::vector<sf::IntRect> m_frames;
    int m_currentFrame;
    float m_elapsedTime;

    sf::Sprite m_sprite;
};
