#include "Camera.h"

Camera::Camera(sf::RenderWindow& window, sf::Vector2f target)
	: m_window(window)
	, m_target(target)
	, m_speed(5.0f) // adjust as needed
	, m_view(window.getDefaultView())
    , m_boardSize(0, 0)
{
	m_view.zoom(0.25f);
	m_view.setCenter(0, 0);
}

void Camera::setBoardSize(sf::Vector2f boardSize)
{
	m_boardSize = boardSize;
}

void Camera::update(sf::Time dt)
{
    sf::Vector2f desiredPos = m_target;

    // smoothly move the camera towards the desired position
    sf::Vector2f diff = desiredPos - m_view.getCenter();
    sf::Vector2f displacement = diff * m_speed * dt.asSeconds();
    float maxDisplacement = 50.0f;
    displacement.x = std::max(std::min(displacement.x, maxDisplacement), -maxDisplacement);
    displacement.y = std::max(std::min(displacement.y, maxDisplacement), -maxDisplacement);
    m_view.move(displacement);

    // set the camera view on the window
    m_window.setView(m_view);
}

void Camera::setTarget(sf::Vector2f target)
{
	m_target = sf::Vector2f(std::max(target.x, m_view.getSize().x / 2), 
        std::max(target.y, m_view.getSize().y / 2));
    m_target = sf::Vector2f(std::min(m_target.x, m_boardSize.x - m_view.getSize().x / 2),
        std::min(m_target.y, m_boardSize.y - m_view.getSize().y / 2));
}

void Camera::pan(Direction direction) {
    switch (direction)
    {
	case Direction::UP:
		setTarget(m_target + sf::Vector2f(0, -m_speed));
		break;
	case Direction::DOWN:
		setTarget(m_target + sf::Vector2f(0, m_speed));
		break;
	case Direction::LEFT:
		setTarget(m_target + sf::Vector2f(-m_speed, 0));
		break;
	case Direction::RIGHT:
		setTarget(m_target + sf::Vector2f(m_speed, 0));
		break;
	}
}

void Camera::zoom(float zoom)
{
	m_view.zoom(zoom);
	setTarget(m_target);
}
