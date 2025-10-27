#include "LevelLoader.h"
#include <fstream>
#include <iostream>

LevelLoader::LevelLoader(sf::Vector2f tileSize)
{
	pTileSize = tileSize;
	pLevelGrid = new Tile**[1];
	for (int y = 0; y < 1; ++y) {
		pLevelGrid[y] = new Tile*[1];
	}
	pLevelWidth = 1;
	pLevelHeight = 1;
}

LevelLoader::~LevelLoader()
{
	for (int y = 0; y < pLevelHeight; y++) {
		for (int x = 0; x < pLevelWidth; x++){
			delete pLevelGrid[y][x];
		}
		delete[] pLevelGrid[y];
	}
	delete[] pLevelGrid;
}

bool LevelLoader::loadFromFile(const std::string& path)
{
	std::fstream file;

	file.open(path, std::ios::in);
	if (!file.is_open()) {
		std::cerr << "Failed to open level file: " << path << std::endl;
		return false;
	}
	else {
		std::string line;
		std::getline(file, line);
		size_t pos = line.find('x');
		std::string widthStr = line.substr(0, pos);
		std::string heightStr = line.substr(pos + 1);
		pLevelWidth = std::stoi(widthStr);
		pLevelHeight = std::stoi(heightStr);
;
		pLevelGrid = new Tile** [pLevelHeight];
		for (int y = 0; y < pLevelHeight; y++) {
			pLevelGrid[y] = new Tile* [pLevelWidth];
		}
	}
}
