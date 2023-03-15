#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Solver.hpp"
#include "Renderer.hpp"

using namespace std;

int main()
{
    // Setup window
    int window_width = 800;
    int window_height = 800;


    sf::RenderWindow window(sf::VideoMode(window_width, window_height), "Verlet Integration!!");


    // setup vars for whole program
    Solver solver;
    Renderer renderer{ window };
    sf::Vector2f middle_screen = { static_cast<float> (window_width / 2), static_cast<float> (window_height / 2) };
    float object_spawn_rate = .01;
    int object_max = 200;

    solver.setGravityCenter({ window_width / 2.f, window_height / 2.f });


    vector<sf::Time> frames_in_second_vector;

    sf::Clock clock;


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Equal) {
                        solver.setGravityValue(solver.getGravityValue() + 200);
                    }
                    if (event.key.code == sf::Keyboard::Hyphen) {
                        solver.setGravityValue(solver.getGravityValue() - 200);
                    }

                    break;
                default:
                    break;
            }
            
        }

        while (clock.getElapsedTime().asSeconds() > solver.getObjectCount() * object_spawn_rate && solver.getObjectCount() < object_max) {
            auto& object = solver.makeObject(sf::Vector2f(static_cast<int8_t> (rand() % window_width), static_cast<int8_t> (rand() % window_height)), 10);
            object.color = {static_cast<sf::Uint8> ( rand() % 255),static_cast<sf::Uint8> ( rand() % 255), static_cast<sf::Uint8> ( rand() % 255)};
        }

        frames_in_second_vector.emplace_back(clock.getElapsedTime());

        vector<sf::Time> temp_frames_vector;
        for (sf::Time time : frames_in_second_vector) { 
            if ((clock.getElapsedTime() - time).asSeconds() < 1) {
                temp_frames_vector.emplace_back(time);
            }
        }
        frames_in_second_vector = temp_frames_vector;
        
        cout << "Frames in last second: " << frames_in_second_vector.size() << endl;

        solver.update();
        window.clear(sf::Color::Black);
        renderer.render(solver);
        window.display();
    }

    return 0;
}