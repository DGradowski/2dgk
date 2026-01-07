#include "player/PhysicsComponent.h"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/System/Vector2.hpp"
#include "player/PlayerObject.h"
#include <iostream>
#include <memory>
#include <algorithm>
#include <cmath>

PhysicsComponent::PhysicsComponent()
{
}

PhysicsComponent::~PhysicsComponent()
{
}

void PhysicsComponent::updateVelocity(PlayerObject& player, float dt)
{
    if (player.MovementVector.x != 0)
    {
        player.Velocity.x += player.MovementVector.x * mAcceleration * dt;
    }
    else
    {
        if (player.Velocity.x > 0)
        {
            player.Velocity.x -= mDeccelartion * dt;
            if (player.Velocity.x < 0) player.Velocity.x = 0;
        }
        else if (player.Velocity.x < 0)
        {
            player.Velocity.x += mDeccelartion * dt;
            if (player.Velocity.x > 0) player.Velocity.x = 0;
        }
    }

    if (player.MovementVector.y != 0)
    {
        player.Velocity.y += player.MovementVector.y * mAcceleration * dt;
    }
    else
    {
        if (player.Velocity.y > 0)
        {
            player.Velocity.y -= mDeccelartion * dt;
            if (player.Velocity.y < 0) player.Velocity.y = 0;
        }
        else if (player.Velocity.y < 0)
        {
            player.Velocity.y += mDeccelartion * dt;
            if (player.Velocity.y > 0) player.Velocity.y = 0;
        }
    }

    if (player.Velocity.x > mMaxVelocity) player.Velocity.x = mMaxVelocity;
    if (player.Velocity.x < -mMaxVelocity) player.Velocity.x = -mMaxVelocity;

    if (player.Velocity.y > mMaxVelocity) player.Velocity.y = mMaxVelocity;
    if (player.Velocity.y < -mMaxVelocity) player.Velocity.y = -mMaxVelocity;

    std::cout << player.Velocity.x << ":" << player.Velocity.y << std::endl;
}

void PhysicsComponent::draw(PlayerObject& player, sf::RenderWindow& window)
{
    mCollider->setPosition(player.Position + mColliderPosition);
    window.draw(*mCollider);
}

BoxPhysicsComponent::BoxPhysicsComponent(sf::Vector2f colliderSize, sf::Vector2f colliderPosition)
{
    mCollider = std::make_shared<sf::RectangleShape>(colliderSize);
    mCollider->setFillColor(sf::Color::Red);
    mColliderPosition = colliderPosition;
}

void BoxPhysicsComponent::update(PlayerObject& player, float dt, const std::vector<sf::FloatRect> walls)
{
    updateVelocity(player, dt);

    player.Position.x += player.Velocity.x;
    mCollider->setPosition(player.Position + mColliderPosition);
    sf::FloatRect playerBounds = mCollider->getGlobalBounds();

    for (const auto& wall : walls)
    {
        if (playerBounds.findIntersection(wall))
        {
            if (player.Velocity.x > 0) // W prawo
            {
                player.Position.x = wall.position.x - playerBounds.size.x - mColliderPosition.x;
            }
            else if (player.Velocity.x < 0) // W lewo
            {
                player.Position.x = wall.position.x + wall.size.x - mColliderPosition.x;
            }

            player.Velocity.x = 0;
        }
    }

    player.Position.y += player.Velocity.y;

    mCollider->setPosition(player.Position + mColliderPosition);
    playerBounds = mCollider->getGlobalBounds();

    for (const auto& wall : walls)
    {
        if (playerBounds.findIntersection(wall))
        {
            if (player.Velocity.y > 0)
            {
                player.Position.y = wall.position.y - playerBounds.size.y - mColliderPosition.y;
            }
            else if (player.Velocity.y < 0)
            {

                player.Position.y = wall.position.y + wall.size.y - mColliderPosition.y;
            }

            player.Velocity.y = 0;
        }
    }
    
    mCollider->setPosition(player.Position + mColliderPosition);
}

CirclePhysicsComponent::CirclePhysicsComponent(float colliderRadius, sf::Vector2f colliderPosition)
{
    mCollider = std::make_shared<sf::CircleShape>(colliderRadius);
    mCollider->setFillColor(sf::Color::Green);
    mColliderPosition = colliderPosition;
}

void CirclePhysicsComponent::update(PlayerObject& player, float dt, const std::vector<sf::FloatRect> walls)
{
    updateVelocity(player, dt);

    auto* circleCollider = static_cast<sf::CircleShape*>(mCollider.get());
    float radius = circleCollider->getRadius();

    auto resolveCollision = [&](sf::Vector2f& position, sf::Vector2f& velocity) 
    {
        mCollider->setPosition(position + mColliderPosition);

        sf::Vector2f center = mCollider->getPosition() + sf::Vector2f(radius, radius);

        for (const auto& wall : walls)
        {
            float closestX = std::clamp(center.x, wall.position.x, wall.position.x + wall.size.x);
            float closestY = std::clamp(center.y, wall.position.y, wall.position.y + wall.size.y);

            sf::Vector2f closestPoint(closestX, closestY);
            sf::Vector2f diff = center - closestPoint;

            float distanceSquared = (diff.x * diff.x) + (diff.y * diff.y);

            if (distanceSquared < (radius * radius) && distanceSquared > 0.0001f)
            {
                float distance = std::sqrt(distanceSquared);
                
                float overlap = radius - distance;

                sf::Vector2f normal = diff / distance;

                position += normal * overlap;

                center += normal * overlap; 
                
                if (std::abs(normal.x) > std::abs(normal.y)) velocity.x = 0;
                if (std::abs(normal.y) > std::abs(normal.x)) velocity.y = 0;
            }
        }
    };

    player.Position.x += player.Velocity.x;
    resolveCollision(player.Position, player.Velocity);

    player.Position.y += player.Velocity.y;
    resolveCollision(player.Position, player.Velocity);

    // Finalna aktualizacja pozycji wizualnej collidera
    mCollider->setPosition(player.Position + mColliderPosition);
}