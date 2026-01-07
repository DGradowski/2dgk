#pragma once

#ifndef LEVELLOADER_H
#define LEVELLOADER_H
#include <string>
#include <SFML/Graphics.hpp>
#include <vector>
#include "TileTypes.h"

using TileData = std::vector<std::vector<TileType>>;

class LevelLoader {
public:
	static TileData loadTileData(const std::string& path);
};

#endif // LEVELLOADER_H

