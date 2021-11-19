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
    window.setFramerateLimit(24);
    window.clear(sf::Color::Black);
    for (int i = 0; i < boidsCount; i++)
    {
        std::random_device rd;                          // obtain a random number from hardware
        std::mt19937 gen(rd());                         // seed the generator
        std::uniform_int_distribution<> distrX(50, window_width-50); // define the range
        std::uniform_int_distribution<> distrY(50, window_height-50); // define the range
        std::uniform_int_distribution<> distr2(-3, 3); // define the range

        //init velocity
        int newVelocityX = distr2(gen);
        int newVelocityY = distr2(gen);
        if(newVelocityX == 0)
            newVelocityX = 1;
        if(newVelocityY == 0)
            newVelocityY = 1;
        sf::Vector2f velocity(newVelocityX, newVelocityY);

        //init position
        sf::Vector2f pos(distrX(gen), distrY(gen));  
        

        //init color
        // rgba(52, 73, 94,1.0)
        // rgba(127, 140, 141,1.0)
        // rgba(231, 76, 60,1.0)
        // rgba(243, 156, 18,1.0)
        // rgba(39, 174, 96,1.0)
        // rgba(22, 160, 133,1.0)
        // rgba(41, 128, 185,1.0)
        // rgba(142, 68, 173,1.0)
        std::vector<sf::Color> colors;
        colors.push_back(sf::Color(52, 73, 94, 255));
        colors.push_back(sf::Color(127, 140, 141, 255));
        colors.push_back(sf::Color(231, 76, 60, 255));
        colors.push_back(sf::Color(243, 156, 18, 255));
        colors.push_back(sf::Color(39, 174, 96, 255));
        colors.push_back(sf::Color(22, 160, 133, 255));
        colors.push_back(sf::Color(41, 128, 185, 255));
        colors.push_back(sf::Color(142, 68, 173, 255));
        sf::Color color = colors[rand() % 7];


        sf::CircleShape circle_boids(2);
        circle_boids.setFillColor(color);
        circle_boids.setPosition(pos.x, pos.y);
        Boids boid_object(color,pos,velocity);

        boidsObj.push_back(boid_object);
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

        
        window.clear(sf::Color::White);
        for (int i = 0; i < boids.size(); i++)
        {
            // boids[i].move(boidsObj[i].getVelocity().x, boidsObj[i].getVelocity().y);
            // boidsObj[i].setPositionX(boidsObj[i].getPosition().x + boidsObj[i].getVelocity().x);
            // boidsObj[i].setPositionY(boidsObj[i].getPosition().y + boidsObj[i].getVelocity().y);
            // window.draw(boids[i]);

            // // If boid exits side boundary
            // if (boids[i].getPosition().x > window_width-20 || boids[i].getPosition().x < 20)
            //     boidsObj[i].setVelocityX(- boidsObj[i].getVelocity().x);
                
            // // If boid exits top bottom boundary
            // if (boids[i].getPosition().y > window_height-20 || boids[i].getPosition().y < 20)
            //     boidsObj[i].setVelocityY(- boidsObj[i].getVelocity().y);
            
            boidsObj[i].run(boidsObj);
        
            boids[i].setPosition(boidsObj[i].getPosition().x,boidsObj[i].getPosition().y);
            window.draw(boids[i]);

        }
        window.display();
    }
}