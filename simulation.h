#ifndef SIM_H
#define SIM_H


#include <iostream>
#include <vector>
#include "boids.h"
#include "spatialHash.h"

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

class Simulation {
    public:
        Simulation(int window_width, int window_height,int count);
        void run();
    private:
        sf::RenderWindow window;
        std::vector<Boids> boidsObj;
        SpatialHash grid;
        int window_width;
        int window_height;
        int boidsCount;
};


#endif