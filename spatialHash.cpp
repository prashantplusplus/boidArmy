#include <iostream>
#include <random>
#include <algorithm>
#include "spatialHash.h"
#include "globals.h"


SpatialHash::SpatialHash()
{

}
SpatialHash::SpatialHash(const sf::Vector2i &windowDimensions, int cellSize)
{

    this->cellSize = cellSize;
    this->windowDimensions = windowDimensions;
    this->gridDimensions.x = ceil((float)windowDimensions.x / (float)cellSize);
    this->gridDimensions.y = ceil((float)windowDimensions.y / (float)cellSize);
}

void SpatialHash::addBoid(Boids& boid)
{
    int hashIndex = createIndex((int)boid.getPosition().x, (int)boid.getPosition().x);
    hashGrid[hashIndex].push_back(boid);
    boid.spatialHashIndex = hashIndex;
}

bool operator==(const Boids& left, const Boids& right) {
    return &left == &right;
}

void SpatialHash::removeBoid(Boids boid)
{
    std::vector<Boids>::iterator iter = std::find(hashGrid[boid.spatialHashIndex].begin(), hashGrid[boid.spatialHashIndex].end(), boid);
    if (iter != hashGrid[boid.spatialHashIndex].end())
        hashGrid[boid.spatialHashIndex].erase(iter);
}

void SpatialHash::updateBoid(Boids& boid)
{
    int hashIndex = createIndex((int)boid.getPosition().x, (int)boid.getPosition().x);

    if (hashIndex == boid.spatialHashIndex)
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

    std::vector<Boids> boids = hashGrid[boidIndex];

    res.insert(res.end(), boids.begin(), boids.end());

    //find adjacent grid in all direction
    int xStart = std::max((int)boid.getPosition().x - radius, 0);
    int xEnd = std::min((int)boid.getPosition().x + radius, windowDimensions.x - 1);
    int yStart = std::max((int)boid.getPosition().y - radius, 0);
    int yEnd = std::min((int)boid.getPosition().y + radius, windowDimensions.y - 1);
    for (int i = xStart; i < xEnd; i += gridDimensions.x)
    {
        for (int j = yStart; j < yEnd; j += gridDimensions.y)
        {
            int hashIndex = createIndex(i,j);
            std::vector<Boids> tempBoids = hashGrid[hashIndex];
            res.insert(res.end(), tempBoids.begin(), tempBoids.end());
        }
    }
    
    return res;
}