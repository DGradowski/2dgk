#include "TileFactory.h"
#include <iostream>

TileFactory::TileFactory(sf::Vector2f tileSize) : mTileSize(tileSize)
{
	registerTileType(TileType::Empty, "./res/textures/empty.jpg", false);
	registerTileType(TileType::Grass, "./res/textures/grass.jpg", false);
	registerTileType(TileType::Brick, "./res/textures/brick.jpg", true);
	registerTileType(TileType::Rock, "./res/textures/rock.jpg", true);
}

bool TileFactory::registerTileType(TileType type, const std::string& texturePath, bool isCollidable)
{
	sf::Texture texture;
	if (!texture.loadFromFile(texturePath)) {
		std::cerr << "ERROR: TileFactory failed to load texture: " << texturePath << std::endl;
		return false;
	}
	mAttributes[type] = { std::move(texture), isCollidable };
	return true;
}

std::unique_ptr<Tile> TileFactory::createTile(TileType type, int gridX, int gridY)
{
	auto it = mAttributes.find(type);

	const TileAttributes& attr = it->second;

	sf::Vector2f position = {
		static_cast<float>(gridX) * mTileSize.x,
		static_cast<float>(gridY) * mTileSize.y
	};
	return std::make_unique<Tile>(attr.texture, position, mTileSize, attr.isCollidable, type);
}