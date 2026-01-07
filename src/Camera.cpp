#include "Camera.h"
#include "player/PlayerObject.h"

#include <iostream>
#include <cmath>

Camera::Camera(sf::RenderWindow& window)
	: mWindow(window)
{
	view = mWindow.getDefaultView();
	minViewSize = view.getSize();
}

Camera::~Camera()
{
}

void Camera::setTarget(std::shared_ptr<PlayerObject> pShape)
{
	pTarget = pShape;
}

void Camera::setTarget2(std::shared_ptr<PlayerObject> pShape)
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
	if (!pTarget || !pTarget2) return;
	float targetX = pTarget->Position.x + 15.f  - view.getCenter().x;
	float target2X = pTarget2->Position.x + 15.f - view.getCenter().x;
	view.move({ ((targetX + target2X) / 2.f) * 5.f * deltaTime, 0.f });
	if (view.getCenter().x - view.getSize().x / 2.f <= 0)
	{
		view.move({ (view.getCenter().x - view.getSize().x / 2.f) * -1, 0});
	}
	else if (view.getCenter().x + view.getSize().x / 2.f >= maxX)
	{
		view.move({ maxX - (view.getCenter().x + view.getSize().x / 2.f), 0});
	}
}

void Camera::moveY(float deltaTime)
{
	if (!pTarget || !pTarget2) return;
	float targetY = pTarget->Position.y + 15.f - view.getCenter().y;
	float target2Y = pTarget2->Position.y + 15.f - view.getCenter().y;
	view.move({ 0.f, ((targetY + target2Y) / 2.f) * 5.f * deltaTime });
	if (view.getCenter().y - view.getSize().y / 2.f <= 0)
	{
		view.move({ 0.f , (view.getCenter().y - view.getSize().y / 2.f) * -1 });
	}
	if (view.getCenter().y + view.getSize().y / 2.f >= maxY)
	{
		view.move({ 0 , maxY - (view.getCenter().y + view.getSize().y / 2.f)});
	}
}

void Camera::resize(float deltaTime)
{
	if (!pTarget || !pTarget2) return;

	sf::Vector2f p1 = pTarget->Position;
	sf::Vector2f p2 = pTarget2->Position;

	sf::Vector2f targetCenter = (p1 + p2) / 2.0f;

	float padding = 150.0f; 
	float widthNeeded = std::abs(p1.x - p2.x) + padding;
	float heightNeeded = std::abs(p1.y - p2.y) + padding;

	widthNeeded = std::max(widthNeeded, minViewSize.x);
	heightNeeded = std::max(heightNeeded, minViewSize.y);
	float currentRatio = minViewSize.x / minViewSize.y;
	float neededRatio = widthNeeded / heightNeeded;

	sf::Vector2f targetSize;
	if (neededRatio > currentRatio) {
		targetSize.x = widthNeeded;
		targetSize.y = widthNeeded / currentRatio;
	}
	else {
		targetSize.x = heightNeeded * currentRatio;
		targetSize.y = heightNeeded;
	}

	sf::Vector2f currentSize = view.getSize();
	sf::Vector2f sizeDiff = targetSize - currentSize;

	view.setSize(currentSize + sizeDiff * 5.0f * deltaTime);
}

void Camera::move(float deltaTime)
{
	resize(deltaTime);
	moveX(deltaTime);
	moveY(deltaTime);
	mWindow.setView(view);
}

void Camera::setMaxValues(float x, float y)
{
	maxX = x;
	maxY = y;
}