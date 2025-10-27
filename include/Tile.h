#pragma once

#ifndef TILE_H
#define TILE_H
#include <SFML/Graphics.hpp>

class Tile : public sf::Drawable {
public:
	Tile(const sf::Texture& texture, sf::Vector2f postion, sf::Vector2f size, bool isCollidable, int type);
	~Tile() = default;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	sf::Sprite mSprite;
	bool mCollidable;
	sf::Vector2f mPosition;
	sf::Vector2f mSize;
};

#endif // !TILE_H



