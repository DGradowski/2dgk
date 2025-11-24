#pragma once

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

	void setTarget(std::shared_ptr<sf::Shape> pShape);
	void setTarget2(std::shared_ptr<sf::Shape> pShape);
	void setXAlgorithm(CameraAlgorithm algorithm);
	void setYAlgorithm(CameraAlgorithm algorithm);

	void moveX(float deltaTime);
	void moveY(float deltaTime);

	void move(float deltaTime);

	void resize(float deltaTime);
private:
	sf::RenderWindow& mWindow;
	sf::View view;
	std::shared_ptr<sf::Shape> pTarget;
	std::shared_ptr<sf::Shape> pTarget2;
	CameraAlgorithm xAlgorithm = CameraAlgorithm::Static;
	CameraAlgorithm yAlgorithm = CameraAlgorithm::Static;

	sf::Vector2f pushZoneSize = sf::Vector2f(-50.f, 50.f);
	float pushZoneMaxOffset = 50.f;
	sf::Vector2f minViewSize;

	float zoomSpeed = 5.f;

};

#endif // !CAMERA_H
