#pragma once

#include "SFML/Graphics/Shape.hpp"
#include "SFML/Window/Window.hpp"
#include <memory>
#ifndef PHYSICSCOMPONENT_H
#define PHYSICSCOMPONENT_H
#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/System/Vector2.hpp"
#include <vector>
#include <SFML/Graphics.hpp>

class PlayerObject;

class PhysicsComponent
{
public:
	PhysicsComponent();
	~PhysicsComponent();

	virtual void update(PlayerObject& player, float dt, const std::vector<sf::FloatRect> walls) = 0;
	void draw(PlayerObject& player, sf::RenderWindow& window);
protected:
	void updateVelocity(PlayerObject& player, float dt);

	float mMaxVelocity = 10.f;
	float mAcceleration = 20.f;
	float mDeccelartion = 40.f;
	std::shared_ptr<sf::Shape> mCollider;
	sf::Vector2f mColliderPosition;
};

class BoxPhysicsComponent : public PhysicsComponent
{
public:
	BoxPhysicsComponent(sf::Vector2f colliderSize, sf::Vector2f colliderPosition);
	void update(PlayerObject& player, float dt, const std::vector<sf::FloatRect> walls) override;
};

class CirclePhysicsComponent : public PhysicsComponent
{
public:
	CirclePhysicsComponent(float colliderRadius, sf::Vector2f colliderPosition);
	void update(PlayerObject &player, float dt, const std::vector<sf::FloatRect> walls) override;
};
#endif // !PHYSICSCOMPONENT_H
