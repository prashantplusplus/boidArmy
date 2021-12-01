#include <iostream>
#include <random>
#include <algorithm>
#include "spatialHash.h"
#include "globals.h"


SpatialHash::SpatialHash(const sf::Vector2i &windowDimensions, int cellSize)
{

    this->cellSize = cellSize;
    this->windowDimensions = windowDimensions;
    this->gridDimensions.x = ceil((float)windowDimensions.x / (float)cellSize);
    this->gridDimensions.y = ceil((float)windowDimensions.y / (float)cellSize);
}

void SpatialHash::addBoid(Boids &boid)
{
    int hashIndex = createIndex((int)boid.getPosition().x, (int)boid.getPosition().x);
    hashGrid[hashIndex].insert(boid);
    boid.spatialHashIndex = hashIndex;
}

void SpatialHash::removeBoid(Boids &boid)
{
    hashGrid[boid.spatialHashIndex].erase(boid);
}

void SpatialHash::updateBoid(Boids &boid)
{
    int hashIndex = createIndex((int)boid.getPosition().x, (int)boid.getPosition().x);

    if (key == boid.spatialHashIndex)
    {
        return; //don't update
    }

    removeBoid(boid);
    addBoid(boid);
}

sf::Vector2i SpatialHash::getIndices(sf::Vector2f position)
{
    float x = position.x / windowDimensions.x;
    float y = position.y / windowDimensions.y;

    int indexX = floor(x * (gridDimensions.x - 1));
    int indexY = floor(y * (gridDimensions.y - 1));

    sf::Vector2i temp = sf::Vector2i(indexX, indexY);
    return temp;
}

int SpatialHash::createIndex(int x, int y)
{
    return x + y * gridDimensions.x;
}



std::vector<Boids> SpatialHash::gridSearch(Boids &boid, int radius)
{

    std::vector<Boids> res;

    //insert my own grid
    int boidIndex = boid.spatialHashIndex;

    auto boids = hashGrid[boidIndex];

    res.insert(res.end(), boids.begin(), boids.end());

    //find adjacent grid in all direction
    int xStart = max(boid.getPosition().x - radius, 0);
    int xEnd = min(boid.getPosition().x + radius, windowDimensions.x - 1);
    int yStart = max(boid.getPosition().y - radius, 0);
    int yEnd = min(boid.getPosition().y + radius, windowDimensions.y - 1);
    for (int i = xStart; i < xEnd; i += gridDimensions.x)
    {
        for (int j = yStart; j < yEnd; j += gridDimensions.y)
        {
            int hashIndex = createIndex(i,j);
            auto boids = hashGrid[hashIndex];
            res.insert(res.end(), boids.begin(), boids.end());
        }
    }
    
    return res;
}