#include "Tile.h"

Tile::Tile(const sf::Texture& texture, sf::Vector2f position, sf::Vector2f size, bool isCollidable, TileType type) :
    mSprite(texture),
    mCollidable(isCollidable),
    mType(type)
{
    mSprite.setPosition(position);

    sf::Vector2u textureSize = texture.getSize();

    float scaleX = size.x / textureSize.x;
    float scaleY = size.y / textureSize.y;

    mSprite.setScale({ scaleX, scaleY });

    mSprite.setPosition(position);
}

void Tile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite, states);
}