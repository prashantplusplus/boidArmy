#include <iostream>
#include <vector>
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

#ifndef BOID_H_
#define BOID_H_

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

    void run(std::vector<Boids>& boidsObj,sf::RenderWindow& window);
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
    std::vector<sf::Vector2f> history;
    sf::Vector2f separation(const std::vector<Boids> &boidObj);
    sf::Vector2f alignment(const std::vector<Boids> &boidObj, float power);
    sf::Vector2f cohesion(const std::vector<Boids> &boidObj);

private:
    int ref;
    sf::CircleShape circle_boid;
    sf::Color color;
    sf::Vector2f position;
    sf::Vector2f acceleration;
    sf::Vector2f velocity;
    
};

#endif