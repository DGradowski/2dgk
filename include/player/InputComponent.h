#pragma once

#ifndef INPUTCOMPONENT_H
#define INPUTCOMPONENT_H

#include <SFML/Window.hpp>

class PlayerObject;

class InputComponent
{
public:
	InputComponent();
	~InputComponent();

	void update(PlayerObject& player);

private:
	sf::Keyboard::Key k_Up;
	sf::Keyboard::Key k_Down;
	sf::Keyboard::Key k_Left;
	sf::Keyboard::Key k_Right;
};

#endif // !INPUTCOMPONENT_H
