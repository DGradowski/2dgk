#pragma once

#include "SFML/System/Vector2.hpp"
#ifndef PLAYEROBJECT_H
#define PLAYEROBJECT_H

#include <memory>
#include <SFML/Graphics.hpp>

#include "player/InputComponent.h"
#include "player/PhysicsComponent.h"
#include "player/PlayerGraphics.h"

enum class PlayerState { Idle, Running, Jumping, Falling };

class PlayerObject
{
public:
	PlayerObject(sf::Vector2f position, std::shared_ptr<InputComponent> inputs, std::shared_ptr<PhysicsComponent> physics, std::shared_ptr<PlayerGraphics> graphics);
	~PlayerObject();
	void update(float dt, const std::vector<sf::FloatRect> walls);
	void draw(sf::RenderWindow& window);

	sf::Vector2f Position;
	sf::Vector2f Velocity;
	sf::Vector2f MovementVector;
	PlayerState State;
	bool IsFacingRight;

private:
	std::shared_ptr<InputComponent> mInput;
	std::shared_ptr<PhysicsComponent> mPhysics;
	std::shared_ptr<PlayerGraphics>  mGraphics;
};

#endif // !PLAYEROBJECT_H