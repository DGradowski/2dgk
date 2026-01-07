#pragma once

#ifndef INPUTCOMPONENT_H
#define INPUTCOMPONENT_H

#include <SFML/Window.hpp>

class PlayerObject;

class InputComponent
{
public:
	InputComponent(sf::Keyboard::Key up, sf::Keyboard::Key down, sf::Keyboard::Key left, sf::Keyboard::Key right);
	~InputComponent();

	void update(PlayerObject& player);

private:
	sf::Keyboard::Key kUp;
	sf::Keyboard::Key kDown;
	sf::Keyboard::Key kLeft;
	sf::Keyboard::Key kRight;
};

#endif // !INPUTCOMPONENT_H
