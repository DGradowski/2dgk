#pragma once

#ifndef TILE_H
#define TILE_H
#include <SFML/Graphics.hpp>
#include "TileTypes.h" 

class Tile : public sf::Drawable {
public:
	Tile(const sf::Texture& texture, sf::Vector2f position, sf::Vector2f size, bool isCollidable, TileType type);
	~Tile() = default;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	bool isCollidable() const { return mCollidable; };
	sf::Vector2f getPosition() const { return mSprite.getPosition(); }
	sf::FloatRect getBounds() const { return mSprite.getGlobalBounds(); }

private:
	sf::Sprite mSprite;
	bool mCollidable;
	TileType mType;
};

#endif // !TILE_H



