#include "Camera.h"

#include <iostream>

Camera::Camera(sf::RenderWindow& window)
	: mWindow(window)
{
	view = mWindow.getDefaultView();
}

Camera::~Camera()
{
}

void Camera::setTarget(std::shared_ptr<sf::Shape> pShape)
{
	pTarget = pShape;
}

void Camera::setTarget2(std::shared_ptr<sf::Shape> pShape)
{
	pTarget2 = pShape;
}

void Camera::setXAlgorithm(CameraAlgorithm algorithm)
{
	xAlgorithm = algorithm;
}

void Camera::setYAlgorithm(CameraAlgorithm algorithm)
{
	yAlgorithm = algorithm;
}

void Camera::moveX(float deltaTime)
{
	if (!pTarget) return;
	float targetX = pTarget->getPosition().x - view.getCenter().x;

	float speed = 0.f;
	if (targetX > pushZoneSize.y) {
		float offset = targetX - pushZoneSize.y;
		std::cout << "Offset X: " << offset << std::endl;
		speed = (offset / pushZoneMaxOffset) * 150.f * deltaTime;
	}
	else if (targetX < pushZoneSize.x) {
		float offset = targetX - pushZoneSize.x;
		std::cout << "Offset X: " << offset << std::endl;
		speed = (offset / pushZoneMaxOffset) * 150.f * deltaTime;
	}
	if (speed != 0.f) {
		view.move({speed, 0.f});
	}
}

void Camera::moveY(float deltaTime)
{
	if (!pTarget || !pTarget2) return;
	float targetY = pTarget->getPosition().y - view.getCenter().y;
	float target2Y = pTarget2->getPosition().y - view.getCenter().y;
	view.move({ 0.f, ((targetY * 1.5f + target2Y) / 2.f) * 5.f * deltaTime });
}

void Camera::move(float deltaTime)
{
	moveX(deltaTime);
	moveY(deltaTime);
	mWindow.setView(view);
}