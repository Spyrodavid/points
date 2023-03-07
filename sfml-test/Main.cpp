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
    const int point_density = 3000;

    vector<sf::Vector2f> points;

    for (float x = -input_radius; x <= input_radius + .001; x += (input_radius * 2) / (point_density - 1))
    {
        for (float y = -input_radius; y <= input_radius + .001; y += (input_radius * 2) / (point_density - 1))
        {
            points.push_back({ x, y });
        }
    }

    // math function
    for (auto &point : points) {
        float x = point.x;
        float y = point.y;


        float pdj_a = 0.1;
        float pdj_b = 1.9;
        float pdj_c = -0.8;
        float pdj_d = -1.2;

        x = 1 * (sin(pdj_a * point.y) - cos(pdj_b * point.x));
        y = 1 * (sin(pdj_c * point.x) - cos(pdj_d * point.y));

        point.x = x;
        point.y = y;
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


        if (pixels[(nx + ny * window_width) * 4] > 0) {

            pixels[(nx + ny * window_width) * 4] -= 1; // R?
            pixels[(nx + ny * window_width) * 4 + 1] -= 1; // G?
            pixels[(nx + ny * window_width) * 4 + 2] -= 1; // B?
            pixels[(nx + ny * window_width) * 4 + 3] -= 1; // A?
        }
    }

    
    texture.update(pixels);

    window.clear(sf::Color::Black);
    window.draw(sprite);

    window.display();

    string file_name; //+ std::to_string(rand() % 1000);
    cout << "Enter name for image: ";
    getline(cin, file_name);
    sf::Image out_image;
    out_image.create(window_width, window_height, pixels);
    out_image.saveToFile("C:\\Users\\spyro\\source\\repos\\PointSFML\\sfml-test\\Images\\" + file_name + ".png");
      
    
    

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

        
        
    }

    return 0;
}