#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Solver.hpp"
#include "Renderer.hpp"
#include <string> 

using namespace std;

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

    sf::Uint8* pixels = new sf::Uint8[window_width * window_height * 4]; // * 4 because pixels have 4 components (RGBA)
    
    float input_radius = 3;
    const int point_density = 1000;

    

    
    
    float spread = 1;
    

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

        vector<sf::Vector2f> points;

        for (float x = -input_radius; x <= input_radius + .001; x += (input_radius * 2) / (point_density - 1))
        {
            for (float y = -input_radius; y <= input_radius + .001; y += (input_radius * 2) / (point_density - 1))
            {
                points.push_back({ x, y });
            }
        }

        spread *= 1.3;
        // math function
        for (auto& point : points) {
            point /= 2.f;
            point.x /= ((((rand() * 1.0) / RAND_MAX) * 2) - 1) * spread;
            point.x += cos(point.x) + sin(point.y);
            point.y += sin(point.y);

        }


        for (size_t i = 0; i < window_width * window_height * 4; i++)
        {
            pixels[i] = 255;
        }


        for (auto point : points) {
            float x = point.x;
            float y = point.y;

            /* cout << x << "  ";
             cout << y << "  ";
             cout << endl;*/

            x += input_radius;
            y += input_radius;

            x /= input_radius * 2;
            y /= input_radius * 2;

            x *= window_width;
            y *= window_height;

            int nx = floor(x);
            int ny = floor(y);

            if (nx < 0 || nx >= window_width || ny < 0 || ny >= window_height) {
                continue;
            }

            pixels[(nx + ny * window_width) * 4] -= 50; // R?
            pixels[(nx + ny * window_width) * 4 + 1] -= 50; // G?
            pixels[(nx + ny * window_width) * 4 + 2] -= 50; // B?
            pixels[(nx + ny * window_width) * 4 + 3] -= 50; // A?
        }


        texture.update(pixels);

        window.clear(sf::Color::Black);
        window.draw(sprite);

        window.display();
        
    }

    return 0;
}