#pragma once

#ifndef BALLPHYSICS_H
#define BALLPHYSICS_H

#include <SFML/Graphics.hpp>
#include "balls/Ball.h"

class BallPhysics {
public:
	BallPhysics(bool separating, bool bouncing, sf::RenderWindow& window);
	~BallPhysics() = default;

	void addBall(std::shared_ptr<Ball> ball);
	void update(float deltaTime);
	void draw(sf::RenderWindow& window);

	bool b_separating;
	bool b_bouncing;

private:
	float m_screenWidth;
	float m_screenHeight;

	std::vector<std::shared_ptr<Ball>> m_Balls;

};

#endif // !BALLPHYSICS_H