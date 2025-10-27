#pragma once

#ifndef LEVELLOADER_H
#define LEVELLOADER_H
#include <string>
#include <unordered_map>
#include <SFML/Graphics.hpp>

class Tile;

class LevelLoader
{
public:
	LevelLoader(sf::Vector2f tileSize);
	~LevelLoader();
	bool loadFromFile(const std::string& path);
private:
	std::unordered_map<std::string, const Tile*> pLevelData;
	sf::Vector2f pTileSize;
	Tile*** pLevelGrid;
	int pLevelWidth;
	int pLevelHeight;
};

#endif // LEVELLOADER_H

