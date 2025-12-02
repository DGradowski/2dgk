#include "balls/BallPhysics.h"

BallPhysics::BallPhysics(bool separating, bool bouncing)
	: b_separating(separating), b_bouncing(bouncing)
{
	m_Balls = std::vector<std::shared_ptr<Ball>>();
}

void BallPhysics::addBall(std::shared_ptr<Ball> ball) {
	m_Balls.push_back(ball);
}

void BallPhysics::update(float deltaTime) {
	// Update positions of all balls
	for (auto& ball : m_Balls) {
		ball->update(deltaTime);
	}
	// Handle collisions between balls
	for (size_t i = 0; i < m_Balls.size(); ++i) {
		for (size_t j = i + 1; j < m_Balls.size(); ++j) {
			auto ballA = m_Balls[i];
			auto ballB = m_Balls[j];
			sf::Vector2f posA = ballA->getPosition();
			sf::Vector2f posB = ballB->getPosition();
			sf::Vector2f delta = posB - posA;
			float distSq = delta.x * delta.x + delta.y * delta.y;
			float radiusSum = ballA->getRadius() + ballB->getRadius();
			float radiusSumSq = radiusSum * radiusSum;
			if (distSq < radiusSumSq) {
				if (b_separating) {
					float dist = std::sqrt(distSq);
					sf::Vector2f correction = delta / dist * (radiusSum - dist) / 2.0f;
					ballA->setPosition(posA - correction);
					ballB->setPosition(posB + correction);
				}
				if (b_bouncing) {
					sf::Vector2f velA = ballA->getVelocity();
					sf::Vector2f velB = ballB->getVelocity();
					sf::Vector2f normal = delta / std::sqrt(distSq);
					float relativeVelocity = (velB - velA).x * normal.x + (velB - velA).y * normal.y;
					if (relativeVelocity < 0) {
						sf::Vector2f impulse = normal * relativeVelocity;
						ballA->setVelocity(velA + impulse);
						ballB->setVelocity(velB - impulse);
					}
				}
			}
		}
	}
}