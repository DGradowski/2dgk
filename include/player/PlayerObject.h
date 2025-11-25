#pragma once

#ifndef PLAYEROBJECT_H
#define PLAYEROBJECT_H

#include <SFML/Graphics.hpp>

enum class PlayerState { Idle, Running, Jumping, Falling };

class PlayerObject
{
public:
	PlayerObject() : state(PlayerState::Idle, isFacingRight(true)) {};
	~PlayerObject();

	sf::Vector2f position;
	sf::Vector2f velocity;
	sf::Vector2f movementVector;
	PlayerState state;
	bool isFacingRight;

};

#endif // !PLAYEROBJECT_H