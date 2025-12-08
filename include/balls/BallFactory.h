#pragma

#ifndef BALLFACTORY_H
#define BALLFACTORY_H

#include <SFML/Graphics.hpp>

class Ball;

class BallFactory {
public:
	BallFactory(sf::Texture* texture, sf::Color color) : m_texture(texture), m_color(color) {};
	std::shared_ptr<Ball> createBall(sf::Vector2f pos, sf::Vector2f vel);
private:
	float m_radius = 30.f;
	sf::Texture* m_texture;
	sf::Color m_color;
};

#endif // !BALLFACTORY_H
