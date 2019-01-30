
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

int main()
{
    // Configuration variables
    int windowWidth  = 375;
    int windowHeight = 375;
    unsigned int fps = 60;

    // SFML variables
    sf::Uint32 style = sf::Style::Titlebar |
                       sf::Style::Close |
                       sf::Style::Resize;
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight),
                            "Doom Fire Algorithm",
                            style);
    window.setFramerateLimit(fps);

    // Variables used in the fire algorithm
    // TODO: Change this to its own class
    // TODO: Use dynamic 2d array for the fire data structre
    const int fireWidth  = 25;
    const int fireHeight = 25;
    int fireValues[fireWidth][fireHeight] = {};
    float fireSize = 15.f;

    sf::RectangleShape fireRendering[fireWidth][fireHeight];
    for (int i=0; i < fireWidth; i++) {
        for (int j=0; j < fireHeight; j++) {
            sf::RectangleShape current;
            current = sf::RectangleShape(
                        sf::Vector2f(fireSize, fireSize));
            current.setPosition(i * fireSize, j * fireSize);
            current.setFillColor(sf::Color(0 + 10 * j, 0, 0));

            fireRendering[i][j] = current;
        }
    }


    while (window.isOpen())
    {
        sf::Event e;

        while (window.pollEvent(e))
        {
            switch (e.type)
            {
                case e.Closed:
                    window.close();
                    break;
                default: 
                    break;
            }
        }

        // Clearing background
        window.clear(sf::Color::Black);

        // Drawing objects
        for (int i=0; i < fireWidth; i++) {
            for (int j=0; j < fireHeight; j++) {
                window.draw(fireRendering[i][j]);
            }
        }

        window.display();
    }


    return 0; 
}
