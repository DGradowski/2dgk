#pragma once

#ifndef TILEFACTORY_H
#define TILEFACTORY_H
#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include <memory>
#include "Tile.h"
#include "TileTypes.h"

class TileFactory {
public:
	TileFactory(sf::Vector2f tileSize);

	bool registerTileType(TileType type, const std::string& texturePath, bool isCollidable);

	std::unique_ptr<Tile> createTile(TileType type, int gridX, int gridY);

private:
	struct TileAttributes {
		sf::Texture texture;
		bool isCollidable;
	};

	std::map<TileType, TileAttributes> mAttributes;
	sf::Vector2f mTileSize;
};

#endif // TILEFACTORY_H