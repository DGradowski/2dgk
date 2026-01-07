#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <memory>
#include <random>
#include <algorithm>
#include <vector>
#include <cmath>
#include <iostream>
#include <optional>

#include "LevelLoader.h"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "TileFactory.h"
#include "GameMap.h"
#include "Camera.h"
#include "player/InputComponent.h"
#include "player/PhysicsComponent.h"
#include "player/PlayerGraphics.h"
#include "player/PlayerObject.h"

sf::Vector2i popRandomPosition(std::vector<sf::Vector2i>& positions) {
    if (positions.empty()) return sf::Vector2i(0, 0);

    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, positions.size() - 1);

    int index = distrib(gen);
    sf::Vector2i result = positions[index];

    positions.erase(positions.begin() + index);
    
    return result;
}

void drawOffScreenIndicator(sf::RenderWindow& window, const sf::Vector2f& goalPos, const sf::View& currentView) {
    sf::Vector2f center = currentView.getCenter();
    sf::Vector2f size = currentView.getSize();

    sf::Vector2f direction = goalPos - center;
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length != 0) direction /= length;

    float margin = 50.f;
    float radius = std::min(size.x, size.y) / 2.f - margin;

    sf::Vector2f arrowPos = center + direction * radius;

    sf::ConvexShape arrow;
    arrow.setPointCount(3);
    arrow.setPoint(0, { 0, 0 });
    arrow.setPoint(1, { -10, 20 });
    arrow.setPoint(2, { 10, 20 });
    arrow.setFillColor(sf::Color::Red);
    arrow.setPosition(arrowPos);

    float angle = std::atan2(direction.y, direction.x) * 180.f / 3.14159f;
    
    arrow.setRotation(sf::degrees(angle + 90.f)); 

    window.draw(arrow);
}

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 900, 900 }), "GameDebug Zadanie 5");
    Camera camera(window);
    unsigned int framerate = 60;
    window.setFramerateLimit(framerate);
    camera.setMaxValues(1215, 1215);

    float deltaTime = 1.f / static_cast<float>(framerate);
    const sf::Vector2f TILE_SIZE = { 45.f, 45.f };

    TileFactory tileFactory(TILE_SIZE);
    TileData levelData = LevelLoader::loadTileData("./res/maps/labirynth.txt");
    GameMap gameMap(TILE_SIZE);
    gameMap.loadLevel(levelData, tileFactory);
    std::vector<sf::FloatRect> walls = gameMap.getWalls();

    std::vector<sf::Vector2i> possiblePositions;
    auto resetPositionsPool = [&possiblePositions]() {
        possiblePositions.clear();
        possiblePositions.push_back(sf::Vector2i(4, 4));
        possiblePositions.push_back(sf::Vector2i(24, 4));
        possiblePositions.push_back(sf::Vector2i(24, 24));
        possiblePositions.push_back(sf::Vector2i(4, 24));
    };
    resetPositionsPool();

    // Setup player 1
    std::shared_ptr<InputComponent> inputs1 = std::make_shared<InputComponent>(sf::Keyboard::Key::W, sf::Keyboard::Key::S, sf::Keyboard::Key::A, sf::Keyboard::Key::D);
    std::shared_ptr<PhysicsComponent> physics1 = std::make_shared<CirclePhysicsComponent>(15, sf::Vector2f{ 0, 0 });
    std::shared_ptr<PlayerGraphics> graphics1 = std::make_shared<PlayerGraphics>();
    std::shared_ptr<PlayerObject> playerCircle = std::make_shared<PlayerObject>(sf::Vector2f(0,0), inputs1, physics1, graphics1);
    camera.setTarget(playerCircle);

    // Setup player 2
    std::shared_ptr<InputComponent> inputs2 = std::make_shared<InputComponent>(sf::Keyboard::Key::Up, sf::Keyboard::Key::Down, sf::Keyboard::Key::Left, sf::Keyboard::Key::Right);
    std::shared_ptr<PhysicsComponent> physics2 = std::make_shared<BoxPhysicsComponent>(sf::Vector2f(30, 30), sf::Vector2f{ 0, 0 });
    std::shared_ptr<PlayerGraphics> graphics2 = std::make_shared<PlayerGraphics>();
    std::shared_ptr<PlayerObject> playerSquare = std::make_shared<PlayerObject>(sf::Vector2f(0, 0), inputs2, physics2, graphics2);
    camera.setTarget2(playerSquare);

    sf::RectangleShape goalRect(TILE_SIZE);
    goalRect.setFillColor(sf::Color(255, 255, 0, 128));
    
    auto resetGame = [&]() {
        resetPositionsPool();

        sf::Vector2i pos1 = popRandomPosition(possiblePositions);
        playerCircle->Position = sf::Vector2f(((pos1.x - 1) * 45.f) + 7.5f, ((pos1.y - 1) * 45.f) + 7.5f);
        playerCircle->Velocity = { 0.f, 0.f };

        sf::Vector2i pos2 = popRandomPosition(possiblePositions);
        playerSquare->Position = sf::Vector2f(((pos2.x - 1) * 45.f) + 7.5f, ((pos2.y - 1) * 45.f) + 7.5f);
        playerSquare->Velocity = { 0.f, 0.f };

        sf::Vector2i posGoal = popRandomPosition(possiblePositions);
        goalRect.setPosition({(posGoal.x - 1) * 45.f, (posGoal.y - 1) * 45.f});
    };

    resetGame();

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        playerCircle->update(deltaTime, walls);
        playerSquare->update(deltaTime, walls);
        camera.move(deltaTime);

        sf::FloatRect p1Bounds({playerCircle->Position.x, playerCircle->Position.y}, {30.f, 30.f});
        sf::FloatRect p2Bounds({playerSquare->Position.x, playerSquare->Position.y}, {30.f, 30.f});
        sf::FloatRect goalBounds = goalRect.getGlobalBounds();


        if (p1Bounds.findIntersection(goalBounds))
        {
            std::cout << "Circle won! Restarting..." << std::endl;
            
            window.clear(sf::Color::Black);
            window.draw(gameMap);
            window.draw(goalRect);
            playerCircle->draw(window);
            playerSquare->draw(window);
            window.display();

            sf::sleep(sf::seconds(3.0f));
            
            resetGame();
            continue;
        }
        else if (p2Bounds.findIntersection(goalBounds))
        {
            std::cout << "Square won! Restarting..." << std::endl;
            
            window.clear(sf::Color::Black);
            window.draw(gameMap);
            window.draw(goalRect);
            playerCircle->draw(window);
            playerSquare->draw(window);
            window.display();

            sf::sleep(sf::seconds(3.0f));
            
            resetGame();
            continue;
        }

        window.clear(sf::Color::Black);
        
        window.draw(gameMap);
        window.draw(goalRect);
        
        playerCircle->draw(window);
        playerSquare->draw(window);

        drawOffScreenIndicator(window, goalRect.getPosition() + sf::Vector2f(22.5f, 22.5f), window.getView());

        window.display();
    }
}