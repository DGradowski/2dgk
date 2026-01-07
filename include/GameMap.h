#pragma once

#include "SFML/Graphics/Rect.hpp"
#ifndef GAMEMAP_H
#define GAMEMAP_H
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Tile.h"
#include "TileFactory.h"
#include "LevelLoader.h"

class GameMap : public sf::Drawable {
public:
	GameMap(sf::Vector2f tileSize);

	void loadLevel(const TileData& data, TileFactory& factory);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	Tile* getTile(int gridX, int gridY);

	std::vector<sf::FloatRect> getWalls();

private:
	std::vector<std::vector<std::unique_ptr<Tile>>> mTiles;
	int mWidth = 0;
	int mHeight = 0;
	sf::Vector2f mTileSize;
};

#endif // GAMEMAP_H