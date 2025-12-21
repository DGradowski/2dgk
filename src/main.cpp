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
#include "balls/BallFactory.h"

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


// static bool isPressedP(){
// 	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P)) {
// 		return true;
// 	}
// 	else {
// 		return false;
// 	}
// }


// static bool isPressedO(){
// 	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::O)) {
// 		return true;
// 	}
// 	else {
// 		return false;
// 	}
// }



// //static sf::Vector2f mouseInput(const sf::RenderWindow& window)
// //{
// //	sf::Vector2i mousePos = sf::Mouse::getPosition(window);
// //	//std::cout << "Mouse position: " << mousePos.x << ", " << mousePos.y << std::endl;
// //	return sf::Vector2f(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
// //}

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 900, 900 }), "Zadanie 3 - Dawid Gradowski 251524");
	Camera camera(window);
	unsigned int framerate = 60;
	window.setFramerateLimit(framerate);

	float deltaTime = 1.f / static_cast<float>(framerate);
	const sf::Vector2f TILE_SIZE = { 45.f, 45.f };

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

    TileData levelData = LevelLoader::loadTileData("./res/maps/labirynth.txt");

    GameMap gameMap(TILE_SIZE);
    gameMap.loadLevel(levelData, tileFactory);
	camera.setTarget(player1);
	camera.setTarget2(player2);

	BallPhysics ballPhysics(true, true, window);
	BallFactory bf(&t_moon, sf::Color::White);


	// ballPhysics.addBall(bf.createBall({ 300, 200 }, { 100, 100 }));
	// ballPhysics.addBall(bf.createBall({ 1000, 300 }, { -100, -100 }));
	// ballPhysics.addBall(bf.createBall({ 250, 400 }, { 100, -100 }));
	// ballPhysics.addBall(bf.createBall({ 250, 260 }, { -100, 100 }));
	// ballPhysics.addBall(bf.createBall({ 600, 100 }, { 100, 100 }));
	// ballPhysics.addBall(bf.createBall({ 300, 50 }, { -100, 100 }));

	// ballPhysics.addBall(bf.createBall({ 10, 200 }, { 100, 100 }));
	// ballPhysics.addBall(bf.createBall({ 100, 300 }, { -100, -100 }));
	// ballPhysics.addBall(bf.createBall({ 10, 400 }, { 100, -100 }));
	// ballPhysics.addBall(bf.createBall({ 10, 260 }, { -100, 100 }));
	// ballPhysics.addBall(bf.createBall({ 10, 100 }, { 100, 100 }));
	// ballPhysics.addBall(bf.createBall({ 10, 50 }, { -100, 100 }));
	
	// ballPhysics.addBall(bf.createBall({ 20, 200 }, { 100, 100 }));
	// ballPhysics.addBall(bf.createBall({ 200, 300 }, { -100, -100 }));
	// ballPhysics.addBall(bf.createBall({ 20, 400 }, { 100, -100 }));
	// ballPhysics.addBall(bf.createBall({ 20, 260 }, { -100, 100 }));
	// ballPhysics.addBall(bf.createBall({ 20, 100 }, { 100, 100 }));
	// ballPhysics.addBall(bf.createBall({ 20, 50 }, { -100, 100 }));

	// ballPhysics.addBall(bf.createBall({ 30, 200 }, { 100, 100 }));
	// ballPhysics.addBall(bf.createBall({ 300, 300 }, { -100, -100 }));
	// ballPhysics.addBall(bf.createBall({ 30, 400 }, { 100, -100 }));
	// ballPhysics.addBall(bf.createBall({ 30, 260 }, { -100, 100 }));
	// ballPhysics.addBall(bf.createBall({ 30, 100 }, { 100, 100 }));
	// ballPhysics.addBall(bf.createBall({ 30, 50 }, { -100, 100 }));
	
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

		// ballPhysics.b_separating = !isPressedO();
		// ballPhysics.b_bouncing = !isPressedP();


		ballPhysics.update(deltaTime);
		player1->move(keyboardInput() * 250.f * deltaTime);
		player2->move(keyboardInput2() * 250.f * deltaTime);
        window.clear(sf::Color::Blue);
        window.draw(gameMap);
        window.draw(*player1);
        window.draw(*player2);
		camera.move(deltaTime);
		ballPhysics.draw(window);
        window.display();
    }
}
