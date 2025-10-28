#include "GameMap.h"

GameMap::GameMap(sf::Vector2f tileSize) : mTileSize(tileSize)
{
}

void GameMap::loadLevel(const TileData& data, TileFactory& factory)
{
	if (data.empty()) return;
	mHeight = data.size();
	mWidth = data[0].size();

	mTiles.clear();
	mTiles.resize(mHeight);

	for (int y = 0; y < mHeight; ++y) {
		mTiles[y].resize(mWidth);
		for (int x = 0; x < mWidth; ++x) {
			TileType type = data[y][x]; 
			std::unique_ptr<Tile> newTile = factory.createTile(type, x, y);

			mTiles[y][x] = std::move(newTile);
		}
	}
}

void GameMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (int y = 0; y < mHeight; ++y) {
		for (int x = 0; x < mWidth; ++x) {
			if (mTiles[y][x]) {
				target.draw(*mTiles[y][x], states);
			}
		}
	}
}

Tile* GameMap::getTile(int gridX, int gridY)
{
	if (gridX >= 0 && gridX < mWidth && gridY >= 0 && gridY < mHeight) {
		return mTiles[gridY][gridX].get();
	}
	return nullptr;
}