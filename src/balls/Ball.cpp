#include "balls/Ball.h"

Ball::Ball(float radius, sf::Vector2f position, sf::Vector2f velocity, sf::Texture* texture, sf::Color color)
	: m_radius(radius), v_position(position), v_velocity(velocity), m_shape(radius)
{
	m_shape = sf::CircleShape(radius);
	m_shape.setTexture(texture);
	m_shape.setPosition(v_position);
	m_shape.setFillColor(color);
	m_shape.setOrigin({ radius, radius });
}


void Ball::update(float deltaTime) {
	v_position += v_velocity * deltaTime;
	m_shape.setPosition(v_position);
}

void Ball::draw(sf::RenderWindow& window) const {
	window.draw(m_shape);
}

void Ball::setVelocity(const sf::Vector2f& velocity) {
	v_velocity = velocity;
}

void Ball::setPosition(const sf::Vector2f& position) {
	v_position = position;
	m_shape.setPosition(v_position);
}

sf::Vector2f Ball::getPosition() const {
	return v_position;
}

sf::Vector2f Ball::getVelocity () const {
	return v_velocity;
}

float Ball::getRadius() const {
	return m_radius;
}
