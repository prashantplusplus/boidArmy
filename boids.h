#ifndef BOID_H_
#define BOID_H_

#include <iostream>
#include <vector>
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

class Boids
{
public:
    Boids(sf::Color color, sf::Vector2f position, sf::Vector2f velocity);
    sf::Vector2f getPosition();
    void setVelocityX(float value);
    void setVelocityY(float value);

    sf::Vector2f getVelocity();
    void setPositionX(float value);
    void setPositionY(float value);


    sf::Vector2f getAcceleration();
    void setAccelerationX(float value);
    void setAccelerationY(float value);
    void run(std::vector<Boids>& boidsObj, sf::RenderWindow& window);

    int spatialHashIndex;
    

private:
    int ref;
    sf::CircleShape circle_boid;
    sf::Color color;
    sf::Vector2f position;
    sf::Vector2f acceleration;
    sf::Vector2f velocity;
    std::vector<sf::Vector2f> history;

    void calculateForces(std::vector<Boids> &boidsObj);
    void update(sf::RenderWindow& window);
    void drawBoid(sf::RenderWindow& window);
    void drawTrail(sf::RenderWindow& window);

    void slowDown(float value);
    void updateVelocity();
    void limitVelocity(float maxValue);
    void updatePosition();
    void checkBoundry();
    void applyForce(const sf::Vector2f& force);

    float findDistance(const sf::Vector2f& v);
    float magnitude(sf::Vector2f& v);
    void normalize(sf::Vector2f & v);
    void limit(sf::Vector2f &v,double max);
    float angle(sf::Vector2f &v);

    

    sf::Vector2f separation(std::vector<sf::Vector2f> seperationDiff, int count, float power);
    sf::Vector2f alignment(sf::Vector2f sum, int count, float power);
    sf::Vector2f cohesion(sf::Vector2f sum, int count, float power);
    
};

#endif