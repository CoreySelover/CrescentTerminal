#include "Animation.h"
#include "TextureManager.h"

Animation::Animation(std::string textureFilePath, int x, int y, int width, int height, int numFrames, float frameDuration)
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

void Animation::update(float deltaTime)
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

void Animation::setPosition(sf::Vector2f position)
{
	m_sprite.setPosition(position);
}

sf::Vector2f Animation::getPosition()
{
	return m_sprite.getPosition();
}

sf::Vector2f Animation::getSize()
{
	return sf::Vector2f(m_frameWidth, m_frameHeight);
}

void Animation::draw(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}
