#include <iostream>
#include "simulation.h"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"


Simulation::Simulation(){

}
void Simulation::run(){
    sf::RenderWindow window(sf::VideoMode(200, 200), "Boids Army");
    for (int i = 0; i < 250; i++) {
        sf::CircleShape circle_boids(8,3);
        circle_boids.setFillColor(sf::Color::Green);
        boids.push_back(circle_boids);
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        for (int i = 0; i < boids.size(); i++) {
            window.draw(boids[i]);
            boids[i].setPosition(i+0,i+1);
        }
        window.display();
    }
}