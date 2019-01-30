
#include <iostream>
#include <vector>
#include <cstdlib>
#include <SFML/Graphics.hpp>

// Process and update the values in fireValues
void updateFire(int** fireValues, int fireWidth, int fireHeight) 
{
    int decay = 1;
    int newFireValue = 0;
    for (int i=0; i < fireHeight - 1; i++) {
        for (int j=0; j < fireWidth; j++) {
            decay = (rand() % 3);
            newFireValue = fireValues[i+1][j] - (decay & 1);

            //  If the J value is less than 0, it will change the other
            // side of the fire
            //  If it is greater than the size of the width of the fire,
            // the same will happen
            int newJ = j-decay+1;
            newJ = newJ < 0 ? fireWidth - 1 : newJ;
            newJ = newJ >= fireWidth ? 0 : newJ; 
            fireValues[i][newJ] = newFireValue >= 0 ? newFireValue : 0;
        }
    }
}

// Function to print each position of fireValues
void testPrintFireValues(int ** fireValues, int fireWidth, int fireHeight)
{
    for (int i=0; i<fireHeight; i++) {
        for (int j=0; j<fireWidth; j++) {
            printf("%2i ", fireValues[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void deleteFire(int** fireValues, sf::RectangleShape** fireRendering,
                int fireWidth, int fireHeight)
{
    for (int i=0; i < fireHeight; i++) {
        delete[] fireValues[i];
        delete[] fireRendering[i];
    }

    delete[] fireValues;
    delete[] fireRendering;
}

int main()
{
    // All 36 colors of the fire
    const sf::Color fireColorPalette[37] = {
        sf::Color(7,7,7), sf::Color(31,7,7),  sf::Color(47,15,7), 
        sf::Color(71,15,7), sf::Color(87,23,7), sf::Color(103,31,7), 
        sf::Color(119,31,7), sf::Color(143,39,7), sf::Color(159,47,7), 
        sf::Color(175,63,7), sf::Color(191,71,7), sf::Color(199,71,7), 
        sf::Color(223,79,7), sf::Color(223,87,7), sf::Color(223,87,7), 
        sf::Color(215,95,7), sf::Color(215,95,7), sf::Color(215,103,15), 
        sf::Color(207,111,15), sf::Color(207,119,15), sf::Color(207,127,15), 
        sf::Color(207,135,23), sf::Color(199,135,23), sf::Color(199,143,23), 
        sf::Color(199,151,31), sf::Color(191,159,31), sf::Color(191,159,31), 
        sf::Color(191,167,39), sf::Color(191,167,39), sf::Color(191,175,47), 
        sf::Color(183,175,47), sf::Color(183,183,47), sf::Color(183,183,55), 
        sf::Color(207,207,111),  sf::Color(223,223,159), sf::Color(239,239,199), 
        sf::Color(255,255,255)
    };

    // Variables used in the fire algorithm
    // TODO: Change fire effect to its own class
    const int fireWidth  = 160;
    const int fireHeight = 160;
    float fireSize = 6.f;

    // Creating a dynamic 2D array for the fire
    int** fireValues;
    fireValues = new int*[fireHeight];
    for (int i=0; i < fireHeight; i++) {
        fireValues[i] = new int[fireWidth];
        for (int j=0; j < fireWidth; j++) {
            // Initializes all values as 0
            fireValues[i][j] = 0;
        }
    }

    // Creating the squares that represent the pixels of the fire
    sf::RectangleShape** fireRendering;
    fireRendering = new sf::RectangleShape*[fireHeight];
    for (int i=0; i < fireHeight; i++) {
        fireRendering[i] = new sf::RectangleShape[fireWidth];
        for (int j=0; j < fireWidth; j++) {
            sf::RectangleShape current;
            // Creates a square representing a fire pixel
            current = sf::RectangleShape(
                        sf::Vector2f(fireSize, fireSize));

            // Sets the new square's position in the window
            current.setPosition(j * fireSize, i * fireSize);

            // Sets the default color of each square
            // Looks like fire:
            // current.setFillColor(sf::Color(0 + 10 * j, 0, 0));
            // All the squares are black as default:
            current.setFillColor(sf::Color::Black);

            fireRendering[i][j] = current;
        }
    }

    // Sets the fire source at the last line of the fireValues matrix
    for (int j=0; j < fireWidth; j++) {
        fireValues[fireHeight-1][j] = 36;
    }

    // Configuration variables
    int windowWidth  = fireWidth  * fireSize;
    int windowHeight = fireHeight * fireSize;
    unsigned int fps = 30;

    // SFML variables
    sf::Uint32 style = sf::Style::Titlebar |
                       sf::Style::Close    |
                       sf::Style::Resize;
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight),
                            "Doom Fire Algorithm",
                            style);
    window.setFramerateLimit(fps);

    bool paused = false;
    while (window.isOpen())
    {
        sf::Event e;

        while (window.pollEvent(e))
        {
            switch (e.type)
            {
                case e.Closed:
                    deleteFire(fireValues, fireRendering, fireWidth, fireHeight);
                    paused = true;
                    window.close();
                    break;
                case e.TextEntered:
                    if (e.text.unicode == ' ') {
                        paused = !paused;
                    }
                    if (e.text.unicode == 'p') {
                        testPrintFireValues(fireValues, fireWidth, fireHeight);
                    }
                    break;
                default: 
                    break;
            }
        }

        if (!paused) {
            // Clearing background
            window.clear(sf::Color::Black);

            updateFire(fireValues, fireWidth, fireHeight);
            // rand() % 3 + 1 -> the decay will be a random number <= 3 and >= 1

            // Drawing objects
            for (int i=0; i < fireHeight; i++) {
                for (int j=0; j < fireWidth; j++) {
                    fireRendering[i][j].setFillColor(fireColorPalette[fireValues[i][j]]);
                    window.draw(fireRendering[i][j]);
                }
            }
        }
        window.display();
    }


    return EXIT_SUCCESS; 
}
