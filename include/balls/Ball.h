#pragma once

#ifndef BALL_H
#define BALL_H

#include <SFML/Graphics.hpp>

class Ball {
public:
	Ball(float radius, sf::Vector2f position, sf::Vector2f velocity, sf::Texture* texture, sf::Color color);

	~Ball() = default;

	void update(float deltaTime);

	void draw(sf::RenderWindow& window) const;

	void setVelocity(const sf::Vector2f& velocity);

	void setPosition(const sf::Vector2f& position);

	sf::Vector2f getPosition() const;

	sf::Vector2f getVelocity() const;
	
	float getRadius() const;

private:
	sf::Vector2f v_position;
	sf::Vector2f v_velocity;
	float m_radius;
	sf::CircleShape m_shape;
};

#endif // !BALL_H