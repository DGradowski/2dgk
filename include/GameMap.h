#pragma once

#ifndef GAMEMAP_H
#define GAMEMAP_H
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Tile.h"
#include "TileFactory.h"
#include "LevelLoader.h"
#include "TileTypes.h"

class GameMap : public sf::Drawable {
public:
	GameMap(sf::Vector2f tileSize);

	void loadLevel(const TileData& data, TileFactory& factory);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	Tile* getTile(int gridX, int gridY);

private:
	std::vector<std::vector<std::unique_ptr<Tile>>> mTiles;
	int mWidth = 0;
	int mHeight = 0;
	sf::Vector2f mTileSize;
};

#endif // GAMEMAP_H