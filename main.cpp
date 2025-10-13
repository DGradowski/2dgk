#include <SFML/Graphics.hpp>
#include <cmath>

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 900, 600 }), "SFML works!");
    // Moon
    sf::CircleShape moon(30.f);
    moon.setFillColor(sf::Color::Green);
    // Planet
    sf::ConvexShape planet(6);
    planet.setFillColor(sf::Color::Red);
    planet.setPoint(0, sf::Vector2f(40, 0));
    planet.setPoint(1, sf::Vector2f(80, 20));
    planet.setPoint(2, sf::Vector2f(80, 60));
    planet.setPoint(3, sf::Vector2f(40, 80));
    planet.setPoint(4, sf::Vector2f(0, 60));
    planet.setPoint(5, sf::Vector2f(0, 20));

    float p_x = 200;
    float p_y = 100;

    float m_x = 100;
    float m_y = 100;

    float t = 0;

    sf::Texture t_moon("./assets/textures/moon.jpg");
    sf::Texture t_planet("./assets/textures/planet.jpg");
    moon.setTexture(&t_moon);
    planet.setTexture(&t_planet);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        t += .001f;
        planet.setPosition(sf::Vector2f(450 + (std::sin(t) * p_x) - 40, 300 + (std::cos(t) * p_y) - 40));
        sf::Vector2f p_pos = planet.getPosition();
        moon.setPosition(sf::Vector2f(p_pos.x + 10 + (std::sin((t * 0.5f) + 0.5) * m_x), p_pos.y + 10 + (std::cos((t * 0.5f) + 0.5) * m_y)));
        window.clear(sf::Color::Blue);
        window.draw(moon);
        window.draw(planet);
        window.display();
    }
}
