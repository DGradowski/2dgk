#include "LevelLoader.h"
#include <fstream>
#include <sstream>
#include <iostream>

TileData LevelLoader::loadTileData(const std::string& path)
{
	std::ifstream file(path);
	if (!file.is_open()) {
		std::cerr << "Failed to open level file: " << path << std::endl;
		return {};
	}

	TileData levelData;
	std::string line;
	int width = 0;
	int height = 0;

	if (std::getline(file, line)) {
		size_t pos = line.find('x');
		if (pos != std::string::npos) {
			try {
				width = std::stoi(line.substr(0, pos));
				height = std::stoi(line.substr(pos + 1));
			}
			catch (const std::exception& e) {
				std::cerr << "Error parsing dimensions: " << e.what() << std::endl;
				return {};
			}
		}
	}
	else {
		std::cerr << "Level file is empty or malformed." << std::endl;
		return {};
	}

    for (int y = 0; y < height; ++y) {
        if (std::getline(file, line)) {

            std::vector<TileType> row;

            for (char tileChar : line) {
                if (std::isdigit(tileChar)) {
                    int tileInt = tileChar - '0';

                    row.push_back(static_cast<TileType>(tileInt));
                }
                else {
                    std::cerr << "Warning: Skipping non-digit character '" << tileChar << "' in row " << y << std::endl;
                }
            }

            if (row.size() != width) {
                std::cerr << "Row " << y << " has incorrect width (" << row.size() << " instead of " << width << ") [Full line: " << line << "]" << std::endl;
            }

            levelData.push_back(std::move(row));
        }
        else {
            std::cerr << "Error: Expected row " << y << " but reached end of file." << std::endl;
            break;
        }
    }

    return levelData;
}