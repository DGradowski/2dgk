#pragma once

#ifndef TILE_H
#define TILE_H
#include <SFML/Graphics.hpp>

class Tile
{
public:
	Tile(sf::Texture texture, sf::Vector2f size, sf::Vector2f position, bool isCollidable = false, sf::Color color = sf::Color::White);
	~Tile();

	void setRelativePosition(sf::Vector2f cameraPosition);

	sf::RectangleShape* getRectangleShape() const { return pRectangle; }

private:
	sf::Texture pTexture;
	sf::Color pColor;
	sf::Vector2f pSize;
	sf::Vector2f pPosition;
	bool pIsCollidable = false;

	sf::RectangleShape *pRectangle;
};

#endif // !TILE_H



