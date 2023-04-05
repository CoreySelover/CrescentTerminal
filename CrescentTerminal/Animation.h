#pragma once

#include <SFML/Graphics.hpp>

class Animation
{
public:
    Animation(sf::Texture* texture, int x, int y, int width, int height, int numFrames, float frameDuration)
    {
        m_texture = texture;
        m_frameWidth = width;
        m_frameHeight = height;
        m_numFrames = numFrames;
        m_frameDuration = frameDuration;

        m_frames.reserve(numFrames);

        for (int i = 0; i < numFrames; i++)
        {
            sf::IntRect frameRect(x + i * width, y, width, height);
            m_frames.push_back(frameRect);
        }

        m_currentFrame = 0;
        m_elapsedTime = 0.0f;

        m_sprite.setTexture(*m_texture);
        m_sprite.setTextureRect(m_frames[m_currentFrame]);
    }

    void update(float deltaTime)
    {
        m_elapsedTime += deltaTime;

        if (m_elapsedTime >= m_frameDuration)
        {
            m_elapsedTime -= m_frameDuration;

            m_currentFrame++;

            if (m_currentFrame >= m_numFrames)
            {
                m_currentFrame = 0;
            }

            m_sprite.setTextureRect(m_frames[m_currentFrame]);
        }
    }

    void setPosition(float x, float y)
    {
        m_sprite.setPosition(x, y);
    }

    void draw(sf::RenderWindow& window)
    {
        window.draw(m_sprite);
    }

private:
    sf::Texture* m_texture;
    int m_frameWidth;
    int m_frameHeight;
    int m_numFrames;
    float m_frameDuration;

    std::vector<sf::IntRect> m_frames;
    int m_currentFrame;
    float m_elapsedTime;

    sf::Sprite m_sprite;
};