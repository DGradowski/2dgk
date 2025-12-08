#include "balls/BallFactory.h"
#include "balls/Ball.h"

std::shared_ptr<Ball> BallFactory::createBall(sf::Vector2f pos, sf::Vector2f vel)
{
	return std::make_shared<Ball>(m_radius, pos, vel, m_texture, m_color);
}
