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
    //sf::Texture backgroundT;
    //backgroundT.loadFromFile("./tank.jpg");
    //sf::Sprite s(backgroundT);
    window.setFramerateLimit(60);

    window.clear(sf::Color::White);
    for (int i = 0; i < boidsCount; i++)
    {
        std::random_device rd;                          // obtain a random number from hardware
        std::mt19937 gen(rd());                         // seed the generator
        std::uniform_int_distribution<> distrX(50, window_width-50); // define the range
        std::uniform_int_distribution<> distrY(50, window_height-50); // define the range
        std::uniform_int_distribution<> distr2(-4, 4); // define the range

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

        Boids boid_object(color,pos,velocity);

        boidsObj.push_back(boid_object);
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
        //window.draw(s);
        
        for (int i = 0; i < boidsObj.size(); i++)
        {   
            boidsObj[i].run(boidsObj,window);
        }
        
        
        
        window.display();
    }
}