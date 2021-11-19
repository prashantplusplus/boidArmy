#include <iostream>
#include <vector>
#include "boids.h"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

#ifndef SIM_H
#define SIM_H

class Simulation {
    public:
        Simulation(int window_width, int window_height,int count);
        void run();
    private:
        sf::RenderWindow window;
        std::vector<sf::CircleShape> boids;
        std::vector<Boids> boidsObj;
        int window_width;
        int window_height;
        int boidsCount;
};


#endif