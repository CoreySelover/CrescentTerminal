#pragma once

// SFML
#include <SFML/Graphics.hpp>

// Crescent Terminal
#include "TextureManager.h"

class Animation
{
public:
    Animation(std::string textureFilePath, int x, int y, int width, int height, int numFrames, float frameDuration)
    {

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

        m_sprite.setTexture(TextureManager::getTexture(textureFilePath));

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

    void setPosition(sf::Vector2f position)
    {
        m_sprite.setPosition(position);
    }

    sf::Vector2f getPosition()
    {
		return m_sprite.getPosition();
	}

    sf::Vector2f getSize()
    {
		return sf::Vector2f(m_frameWidth, m_frameHeight);
	}

    void draw(sf::RenderWindow& window)
    {
        window.draw(m_sprite);
    }

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
