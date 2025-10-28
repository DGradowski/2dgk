#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>
#include "LevelLoader.h"
#include "TileFactory.h"
#include "GameMap.h"
#include "TileTypes.h"

static sf::Vector2f keyboardInput()
{
	sf::Vector2f movement(0.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
		movement.y -= 1.f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		movement.y += 1.f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		movement.x -= 1.f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		movement.x += 1.f;
	if (movement.length() != 0) {
		std::cout << "Player 1 movement: " << movement.x << ", " << movement.y << std::endl;
		movement = movement.normalized();
	}
	return movement;
}

static sf::Vector2f mouseInput(const sf::RenderWindow& window)
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);
	std::cout << "Mouse position: " << mousePos.x << ", " << mousePos.y << std::endl;
	return sf::Vector2f(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
}

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 900, 600 }), "Zadanie 3 - Dawid Gradowski 251524");
	unsigned int framerate = 60;
	window.setFramerateLimit(framerate);

	float deltaTime = 1.f / static_cast<float>(framerate);
	const sf::Vector2f TILE_SIZE = { 48.f, 48.f };

	// Player 1
	sf::RectangleShape player1(sf::Vector2f(60.f, 60.f));
	player1.setFillColor(sf::Color::Yellow);

    // Player 2
    sf::CircleShape player2(30.f);
    player2.setFillColor(sf::Color (0,255,0,128));

    float t = 0;

    sf::Texture t_moon("./res/textures/moon.jpg");
    sf::Texture t_planet("./res/textures/planet.jpg");
    player1.setTexture(&t_moon);
    player2.setTexture(&t_planet);

    TileFactory tileFactory(TILE_SIZE);

    TileData levelData = LevelLoader::loadTileData("./res/maps/map.txt");

    GameMap gameMap(TILE_SIZE);
    gameMap.loadLevel(levelData, tileFactory);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

		// Player 1 movement
		
		player1.move(keyboardInput() * 250.f * deltaTime);

		sf::Vector2f p2_pos = player2.getPosition();

		float t = 0.9f;

		player2.setPosition({ (p2_pos.x * t + mouseInput(window).x * (1.f - t)), (p2_pos.y * t + mouseInput(window).y * (1.f - t)) });

        window.clear(sf::Color::Blue);
        window.draw(gameMap);
        window.draw(player1);
        window.draw(player2);
        window.display();
    }
}
