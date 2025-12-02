#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>
#include "LevelLoader.h"
#include "TileFactory.h"
#include "GameMap.h"
#include "TileTypes.h"
#include "Camera.h"
#include "balls/BallPhysics.h"
#include "balls/Ball.h"

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
		//std::cout << "Player 1 movement: " << movement.x << ", " << movement.y << std::endl;
		movement = movement.normalized();
	}
	return movement;
}

static sf::Vector2f keyboardInput2()
{
	sf::Vector2f movement(0.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
		movement.y -= 1.f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
		movement.y += 1.f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
		movement.x -= 1.f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
		movement.x += 1.f;
	if (movement.length() != 0) {
		//std::cout << "Player 1 movement: " << movement.x << ", " << movement.y << std::endl;
		movement = movement.normalized();
	}
	return movement;
}

//static sf::Vector2f mouseInput(const sf::RenderWindow& window)
//{
//	sf::Vector2i mousePos = sf::Mouse::getPosition(window);
//	//std::cout << "Mouse position: " << mousePos.x << ", " << mousePos.y << std::endl;
//	return sf::Vector2f(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
//}

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 900, 600 }), "Zadanie 3 - Dawid Gradowski 251524");
	Camera camera(window);
	unsigned int framerate = 60;
	window.setFramerateLimit(framerate);

	float deltaTime = 1.f / static_cast<float>(framerate);
	const sf::Vector2f TILE_SIZE = { 48.f, 48.f };

	// Player 1
	std::shared_ptr<sf::RectangleShape> player1 = std::make_shared<sf::RectangleShape>(sf::Vector2f(60.f, 60.f));
	player1->setPosition({ 100.f, 100.f });
	player1->setFillColor(sf::Color::Yellow);

    // Player 2
	std::shared_ptr<sf::CircleShape> player2 = std::make_shared<sf::CircleShape>(30.f);
    player2->setFillColor(sf::Color (0,255,0,128));

    float t = 0;

    sf::Texture t_moon("./res/textures/moon.jpg");
    sf::Texture t_planet("./res/textures/planet.jpg");
    player1->setTexture(&t_moon);
    player2->setTexture(&t_planet);

    TileFactory tileFactory(TILE_SIZE);

    TileData levelData = LevelLoader::loadTileData("./res/maps/map.txt");

    GameMap gameMap(TILE_SIZE);
    gameMap.loadLevel(levelData, tileFactory);
	camera.setTarget(player1);
	camera.setTarget2(player2);

	BallPhysics ballPhysics(true, true);
	std::shared_ptr<Ball> ball1 = std::make_shared<Ball>(40.f, sf::Vector2f( 100.f, 115.f ), sf::Vector2f(300.f, 0.f), &t_moon, sf::Color::White);
	std::shared_ptr<Ball> ball2 = std::make_shared<Ball>(30.f, sf::Vector2f( 500.f, 100.f ), sf::Vector2f(-300.f, 0.f), &t_moon, sf::Color::Red);
	std::shared_ptr<Ball> ball3 = std::make_shared<Ball>(20.f, sf::Vector2f(200.f, 200.f), sf::Vector2f(30.f, 0.f), &t_moon, sf::Color::White);
	std::shared_ptr<Ball> ball4 = std::make_shared<Ball>(20.f, sf::Vector2f(400.f, 200.f), sf::Vector2f(-30.f, 0.f), &t_moon, sf::Color::Red);

	std::shared_ptr<Ball> ball5 = std::make_shared<Ball>(20.f, sf::Vector2f(300.f, 200.f), sf::Vector2f(0.f, -50.f), &t_moon, sf::Color::White);
	std::shared_ptr<Ball> ball6 = std::make_shared<Ball>(30.f, sf::Vector2f(300.f, 100.f), sf::Vector2f(0.f, 50.f), &t_moon, sf::Color::Red);


	ballPhysics.addBall(ball1);
	ballPhysics.addBall(ball2);
	ballPhysics.addBall(ball3);
	ballPhysics.addBall(ball4);
	ballPhysics.addBall(ball5);
	ballPhysics.addBall(ball6);
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

		ballPhysics.update(deltaTime);
		player1->move(keyboardInput() * 250.f * deltaTime);
		player2->move(keyboardInput2() * 250.f * deltaTime);
        window.clear(sf::Color::Blue);
        window.draw(gameMap);
        window.draw(*player1);
        window.draw(*player2);
		camera.move(deltaTime);
		ball1->draw(window);
		ball2->draw(window);
		ball3->draw(window);
		ball4->draw(window);
		ball5->draw(window);
		ball6->draw(window);
        window.display();
    }
}
