#ifndef SPA_H
#define SPA_H


#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
#include "boids.h"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"




class SpatialHash {
    public:
        SpatialHash();
        SpatialHash(const sf::Vector2i& winDim, int cellSize);
        void addBoid(Boids& boid);
        void removeBoid(Boids& boid);
        void updateBoid(Boids& boid);
        void clear();
        std::vector<Boids> gridSearch(Boids& boid, int radius);
        std::unordered_map<int, std::set<Boids> > hashGrid;
    private:
        int cellSize;
        sf::Vector2i gridDimensions; 
        sf::Vector2i windowDimensions;
        int createIndex(int x, int y);
        sf::Vector2i getIndices(sf::Vector2f position);
};

#endif