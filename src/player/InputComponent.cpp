#include "player/InputComponent.h"
#include "SFML/System/Vector2.hpp"
#include "player/PlayerObject.h"

InputComponent::InputComponent(sf::Keyboard::Key up, sf::Keyboard::Key down, sf::Keyboard::Key left, sf::Keyboard::Key right)
    : kUp(up), kDown(down), kLeft(left), kRight(right)
{
    
}

InputComponent::~InputComponent()
{
}

void InputComponent::update(PlayerObject& player)
{
	player.MovementVector = sf::Vector2f(0, 0);
	if (sf::Keyboard::isKeyPressed(kUp)) player.MovementVector.y -= 1.f;
	if (sf::Keyboard::isKeyPressed(kDown)) player.MovementVector.y += 1.f;
	if (sf::Keyboard::isKeyPressed(kLeft)) player.MovementVector.x -= 1.f;
	if (sf::Keyboard::isKeyPressed(kRight)) player.MovementVector.x += 1.f;
	if (player.MovementVector.length() != 0)
	{
		player.MovementVector = player.MovementVector.normalized();
	}
	else
	{
		player.MovementVector = sf::Vector2f(0, 0);
	}
}
