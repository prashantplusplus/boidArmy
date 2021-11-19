#include <iostream>
#include <random>
#include "simulation.h"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

Simulation::Simulation(int window_width, int window_height,int count)
{
    this->boidsCount = count;
    this->window_width = window_width;
    this->window_height = window_height;
}
void Simulation::run()
{
    sf::RenderWindow window(sf::VideoMode(window_width, window_height), "Boids Army");
    window.setFramerateLimit(27);
    for (int i = 0; i < boidsCount; i++)
    {
        sf::CircleShape circle_boids(2);
        circle_boids.setFillColor(sf::Color::Green);
        std::random_device rd;                          // obtain a random number from hardware
        std::mt19937 gen(rd());                         // seed the generator
        
        std::uniform_int_distribution<> distrX(50, window_width-50); // define the range
        std::uniform_int_distribution<> distrY(50, window_height-50); // define the range
        circle_boids.setPosition(distrX(gen), distrY(gen));
        
        std::uniform_int_distribution<> distr2(-3, 3); // define the range
        int newVelocityX = distr2(gen);
        int newVelocityY = distr2(gen);
        if(newVelocityX == 0)
            newVelocityX = 1;
        if(newVelocityY == 0)
            newVelocityY = 1;
        sf::Vector2f v(newVelocityX, newVelocityY);
        
        boidsV.push_back(v);
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

        for (int i = 0; i < boids.size(); i++)
        {
            boids[i].move(boidsV[i].x, boidsV[i].y);
            window.draw(boids[i]);
            // If boid exits side boundary
            if (boids[i].getPosition().x > window_width-20 || boids[i].getPosition().x < 20)
                boidsV[i].x = -boidsV[i].x;
                
            // If boid exits top bottom boundary
            if (boids[i].getPosition().y > window_height-20 || boids[i].getPosition().y < 20)
                boidsV[i].y = -boidsV[i].y;
            
        }
        window.display();
    }
}