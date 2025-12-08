#pragma once

#ifndef PHYSICSCOMPONENT_H
#define PHYSICSCOMPONENT_H

#include <SFML/Graphics.hpp>

class PhysicsComponent
{
public:
	PhysicsComponent();
	~PhysicsComponent();

private:
	const float m_gravity = 980.0f;
	float m_jumpForce;
	sf::FloatRect m_rect;
};



#endif // !PHYSICSCOMPONENT_H
