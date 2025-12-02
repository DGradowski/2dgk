#include "player/InputComponent.h"
#include "player/PlayerObject.h"

InputComponent::InputComponent()
{
	k_Up = sf::Keyboard::Key::I;
	k_Down = sf::Keyboard::Key::K;
	k_Left = sf::Keyboard::Key::J;
	k_Right = sf::Keyboard::Key::L;
}

InputComponent::~InputComponent()
{
}

void InputComponent::update(PlayerObject& player)
{
	player.movementVector = sf::Vector2f(0, 0);
	if (sf::Keyboard::isKeyPressed(k_Up))
		player.movementVector.y -= 1.f;
	if (sf::Keyboard::isKeyPressed(k_Down))
		player.movementVector.y += 1.f;
	if (sf::Keyboard::isKeyPressed(k_Left))
		player.movementVector.x -= 1.f;
	if (sf::Keyboard::isKeyPressed(k_Right))
		player.movementVector.x += 1.f;
	if (player.movementVector.length() != 0) {
		player.movementVector = player.movementVector.normalized();
	}
}
