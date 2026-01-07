#pragma once

#include "player/PlayerObject.h"
#ifndef CAMERA_H
#define CAMERA_H

#include <SFML/Graphics.hpp>

enum class CameraAlgorithm
{
	Static,
	PushZone,
	DualForwardFocus
};

class Camera
{
public:
	Camera(sf::RenderWindow& window);
	~Camera();

	void setTarget(std::shared_ptr<PlayerObject> pShape);
	void setTarget2(std::shared_ptr<PlayerObject> pShape);
	void setXAlgorithm(CameraAlgorithm algorithm);
	void setYAlgorithm(CameraAlgorithm algorithm);
	void moveX(float deltaTime);
	void moveY(float deltaTime);
	void move(float deltaTime);
	void resize(float deltaTime);

	void setMaxValues(float x, float y);

private:
	sf::RenderWindow& mWindow;
	sf::View view;
	std::shared_ptr<PlayerObject> pTarget;
	std::shared_ptr<PlayerObject> pTarget2;
	CameraAlgorithm xAlgorithm = CameraAlgorithm::Static;
	CameraAlgorithm yAlgorithm = CameraAlgorithm::Static;

	sf::Vector2f pushZoneSize = sf::Vector2f(-50.f, 50.f);
	float pushZoneMaxOffset = 50.f;
	sf::Vector2f minViewSize;

	float maxX = 0;
	float maxY = 0;

	float zoomSpeed = 5.f;

};

#endif // !CAMERA_H
