#include "player/PlayerObject.h"
#include "SFML/System/Vector2.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "player/PlayerGraphics.h"
#include "player/InputComponent.h"
#include "player/PhysicsComponent.h"
#include <memory>


PlayerObject::PlayerObject(sf::Vector2f position, std::shared_ptr<InputComponent> inputs, std::shared_ptr<PhysicsComponent> physics, std::shared_ptr<PlayerGraphics> graphics)
{
    Position = position;
    mInput = inputs;
    mGraphics = graphics;
    mPhysics = physics;
    
}

PlayerObject::~PlayerObject()
{

}

void PlayerObject::update(float dt, const std::vector<sf::FloatRect> walls)
{
    mInput->update(*this);
    mPhysics->update(*this, dt, walls);
}

void PlayerObject::draw(sf::RenderWindow& window)
{
    mPhysics->draw(*this, window);
}

