#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string> 
#include <cmath>

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

    int screen_pixels = window_width * window_height;

    sf::Uint8* pixels = new sf::Uint8[screen_pixels * 4]; // * 4 because pixels have 4 components (RGBA)

    float input_radius = 3;
    const int point_density = 3000;

    vector<sf::Vector2f> points;
    sf::Vector3f* discreet_points = new sf::Vector3f[screen_pixels]; // * 4 because pixels have 4 components (RGBA)


    for (float x = -input_radius; x <= input_radius + .001; x += (input_radius * 2) / (point_density - 1))
    {
        for (float y = -input_radius; y <= input_radius + .001; y += (input_radius * 2) / (point_density - 1))
        {
            points.push_back({ x, y });
        }
    }


    int maximum_points = INT_MIN;
    int minimum_points = INT_MAX;
    // Count Points
    for (auto point : points) {

        // Math function
        sf::Vector2f old_point(point);

        float pdj_a = 0.1;
        float pdj_b = 1.9;
        float pdj_c = -0.8;
        float pdj_d = -1.2;

        point.x = 1 * (cos(pdj_a * old_point.y) + cos(pdj_b * old_point.x));
        point.y = 1 * (sin(pdj_c * old_point.x) - cos(pdj_d * point.y));


        // Count points
        float x = point.x;
        float y = point.y;

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

        auto total_vec = point - old_point;
        
        discreet_points[(nx + ny * window_width)] += {total_vec.x, total_vec.y, 1};
      
    }


    // Find min and max
    for (int i = 0; i < screen_pixels; i++) {

        if (maximum_points < discreet_points[i].z) {
            maximum_points = discreet_points[i].z;
        }

        if (minimum_points > discreet_points[i].z) {
            minimum_points = discreet_points[i].z;
        }
    }

    std::cout << minimum_points << endl;
    std::cout << maximum_points << endl;


    // white screen
    for (size_t i = 0; i < screen_pixels * 4; i++)
    {
        pixels[i] = 255;
    }


    // draw points
    for (size_t i = 0; i < screen_pixels; i++)
    {
        int hits = discreet_points[i].z;

        float hits_float01 = log(hits * 1.0 + 1) / log(maximum_points);

        int color_ammt = floor(hits_float01 * 255);

        float angle = atan2(discreet_points[i].y, discreet_points[i].x);
        

        float pi = 3.1415926;
        float r = 0;
        float b = 0;
        //cout << angle;
        if (angle > pi) {
            r = angle * hits;
        }
        else {
            b = -angle * hits;
        }
        
        //int min_val = min(static_cast<int> (discreet_points[i]), 255);
        if (hits > 0) {
            pixels[i * 4] -= color_ammt ; // R?
            pixels[i * 4 + 1] -= color_ammt / r; // G?
            pixels[i * 4 + 2] -= color_ammt / b; // B?
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

float length(sf::Vector3f vec) {
    return sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

float length(sf::Vector2f vec) {
    return sqrt(vec.x * vec.x + vec.y * vec.y);
}

sf::Vector2f normalize(sf::Vector2f vec) {
    return vec / length(vec);
}