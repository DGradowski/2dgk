#include "balls/BallPhysics.h"

BallPhysics::BallPhysics(bool separating, bool bouncing,sf::RenderWindow& window)
	: b_separating(separating), b_bouncing(bouncing)
{
	m_Balls = std::vector<std::shared_ptr<Ball>>();
	m_screenWidth = window.getSize().x;
	m_screenHeight = window.getSize().y;
}

void BallPhysics::addBall(std::shared_ptr<Ball> ball) {
	m_Balls.push_back(ball);
}

void BallPhysics::update(float deltaTime) {
	// Update positions of all balls
	for (auto& ball : m_Balls) {
		ball->update(deltaTime);
	}
	for (size_t i = 0; i < m_Balls.size(); ++i) {
		// Collisions between balls
		auto ballA = m_Balls[i];
		for (size_t j = i + 1; j < m_Balls.size(); ++j) {
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
		// Collisions with walls
		float delta;
		if (ballA->getPosition().x - ballA->getRadius() <= 0) {
			delta = ballA->getPosition().x - ballA->getRadius();
			ballA->setVelocity({ -ballA->getVelocity().x, ballA->getVelocity().y });
			ballA->setPosition({ ballA->getPosition().x - delta, ballA->getPosition().y });
		}
		else if (ballA->getPosition().x + ballA->getRadius() >= m_screenWidth) {
			delta = ballA->getPosition().x + ballA->getRadius() - m_screenWidth;
			ballA->setVelocity({ -ballA->getVelocity().x, ballA->getVelocity().y });
			ballA->setPosition({ ballA->getPosition().x - delta, ballA->getPosition().y });
		}
		if (ballA->getPosition().y - ballA->getRadius() <= 0) {
			delta = ballA->getPosition().y - ballA->getRadius();
			ballA->setVelocity({ ballA->getVelocity().x, -ballA->getVelocity().y });
			ballA->setPosition({ ballA->getPosition().x, ballA->getPosition().y - delta });
		}
		else if (ballA->getPosition().y + ballA->getRadius() >= m_screenHeight) {
			delta = ballA->getPosition().y + ballA->getRadius() - m_screenHeight;
			ballA->setVelocity({ ballA->getVelocity().x, -ballA->getVelocity().y });
			ballA->setPosition({ ballA->getPosition().x, ballA->getPosition().y - delta });
		}
	}
}

void BallPhysics::draw(sf::RenderWindow& window) {
	for (auto& ball : m_Balls) {
		ball->draw(window);
	}
}