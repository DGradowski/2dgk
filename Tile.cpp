#include "Tile.h"

Tile::Tile(sf::Texture texture, sf::Vector2f size, sf::Vector2f position, bool isCollidable, sf::Color color)
{
	pTexture = texture;
	pSize = size;
	pPosition = position;
	pIsCollidable = isCollidable;
	pColor = color;
}

void Tile::setRelativePosition(sf::Vector2f cameraPosition)
{

}