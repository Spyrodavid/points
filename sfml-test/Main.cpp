#include <SFML/Graphics.hpp>
#include <chrono>
#include <iostream>
#include <vector>
#include <string> 
#include <cmath>
#include "Worley.hpp"

using namespace std;
using namespace chrono;

int main()
{

    // Setup window
    const int window_width = 800;
    const int window_height = 800;

    sf::RenderWindow window(sf::VideoMode(window_width, window_height), "Verlet Integration!!");

    sf::Sprite sprite;
    sf::Texture texture;
    texture.create(window_width, window_height);
    sprite.setTexture(texture);

    int screen_pixels = window_width * window_height;

    sf::Uint8* pixels = new sf::Uint8[screen_pixels * 4]; // * 4 because pixels have 4 components (RGBA)


    auto start_draw = high_resolution_clock::now();


    Worley worley;

    // draw points
    for (size_t x = 0; x < window_width; x++)
    {
        for (size_t y = 0; y < window_height; y++)
        {

            float noiseVal = worley.noise(x, y) * 255;
            pixels[(x + y * window_width) * 4] = noiseVal;
            pixels[(x + y * window_width) * 4 + 1] = noiseVal;
            pixels[(x + y * window_width) * 4 + 2] = noiseVal;
            pixels[(x + y * window_width) * 4 + 3] = 255;
        }
    }

    cout << "Duration draw took in s: " << (duration_cast<microseconds> (high_resolution_clock::now() - start_draw)).count() / pow(10., 6.) << endl;


    texture.update(pixels);

    window.clear(sf::Color::Black);
    window.draw(sprite);

    window.display();

    string file_name; 
    cout << "Enter name for image: ";
    getline(cin, file_name);
    sf::Image out_image;
    out_image.create(window_width, window_height, pixels);
    out_image.saveToFile("C:\\Users\\spyro\\source\\repos\\PointSFML\\sfml-test\\Images\\" + file_name + std::to_string(rand() % 10) + ".png");

    int t = 0;


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;

            default:
                break;
            }

        }

        Worley worley;

        // draw points
        for (size_t x = 0; x < window_width; x++)
        {
            for (size_t y = 0; y < window_height; y++)
            {

                float noiseVal = worley.noise(x + t * t, y) * 255;
                pixels[(x + y * window_width) * 4] = noiseVal;
                pixels[(x + y * window_width) * 4 + 1] = noiseVal;
                pixels[(x + y * window_width) * 4 + 2] = noiseVal;
                pixels[(x + y * window_width) * 4 + 3] = 255;
            }
        }

        cout << "Duration draw took in s: " << (duration_cast<microseconds> (high_resolution_clock::now() - start_draw)).count() / pow(10., 6.) << endl;


        texture.update(pixels);

        window.clear(sf::Color::Black);
        window.draw(sprite);

        window.display();

        t++;
    }

    return 0;
}

float length(sf::Vector3f vec) {
    return sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

float length(sf::Vector2f vec) {
    return sqrt(vec.x * vec.x + vec.y * vec.y);
}

sf::Vector2f normalize(sf::Vector2f vec) {
    return vec / length(vec);
}