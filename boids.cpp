#include <iostream>
#include <random>
#include "simulation.h"
#include "boids.h"
#include "globals.h"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#define PI 3.14159263

Boids::Boids(sf::Color color, sf::Vector2f position, sf::Vector2f velocity)
{
    this->circle_boid = sf::CircleShape(3);
    circle_boid.setFillColor(color);
    circle_boid.setPosition(position.x, position.y);
    this->color = color;
    this->position = position;
    this->velocity = velocity;
    this->acceleration = sf::Vector2f(0, 0);
}

sf::Vector2f Boids::getPosition()
{
    return position;
}

sf::Vector2f Boids::getVelocity()
{
    return velocity;
}

sf::Vector2f Boids::getAcceleration()
{
    return acceleration;
}

void Boids::setPositionX(float value)
{
    position.x = value;
}

void Boids::setPositionY(float value)
{
    position.x = value;
}

void Boids::setVelocityX(float value)
{
    velocity.x = value;
}

void Boids::setVelocityY(float value)
{
    velocity.y = value;
}

void Boids::setAccelerationX(float value)
{
    acceleration.x = value;
}

void Boids::setAccelerationY(float value)
{
    acceleration.y = value;
}

void Boids::run(std::vector<Boids> &boidsObj, sf::RenderWindow &window)
{
    calculateForces(boidsObj);
    update(window);
}
void Boids::calculateForces(std::vector<Boids> &boidsObj){
    int alignCount = 0;
    int cohesionCount = 0;
    int seperationCount = 0;

    float alignNeighborDist = 50;
    float cohesionNeighborDist = 50;
    float seperationNeighborDist = 6;

    sf::Vector2f alignSum(0, 0);
    sf::Vector2f cohesionSum(0, 0);
    std::vector<sf::Vector2f> seperationDiff;
    for (int i = 0; i < boidsObj.size(); i++)
    {
        float d = findDistance(boidsObj[i].position);
        if (d > 0)
        {
            //alignment
            if (d < alignNeighborDist)
            {
                alignSum.x += boidsObj[i].velocity.x;
                alignSum.y += boidsObj[i].velocity.y;
                alignCount++;
            }

            //cohesion
            if (d < cohesionNeighborDist)
            {
                cohesionSum.x += boidsObj[i].position.x;
                cohesionSum.y += boidsObj[i].position.y;
                cohesionCount++;
            }

            //seperation
            if (d < seperationNeighborDist)
            {
                sf::Vector2f diff(0, 0);
                diff.x = position.x - boidsObj[i].position.x;
                diff.y = position.y - boidsObj[i].position.y;

                normalize(diff);

                diff.x /= d;
                diff.y /= d;

                seperationDiff.push_back(diff);
                seperationCount++;
            }
        }

    }

    if (alignCount > 0)
    {
        sf::Vector2f alignForce;
        alignForce = alignment(alignSum, alignCount, 1.0);
        applyForce(alignForce);
    }

    if (cohesionCount > 0)
    {
        sf::Vector2f cohesionForce;
        cohesionForce = cohesion(cohesionSum, alignCount, 1.0);
        applyForce(cohesionForce);
    }

    if (seperationCount > 0)
    {
        sf::Vector2f seperationForce;
        seperationForce = separation(seperationDiff, seperationCount, 1.0);
        applyForce(seperationForce);
    }
}
void Boids::update(sf::RenderWindow &window)
{
    //slowDown(0.9f);
    updateVelocity();
    limitVelocity(6);
    updatePosition();
    checkBoundry();
    drawBoid(window);
    drawTrail(window);
}

void Boids::drawBoid(sf::RenderWindow &window)
{
    circle_boid.setPosition(position.x, position.y);
    //float theta = angle(velocity);
    //circle_boid.setRotation(theta);
    window.draw(circle_boid);
}
void Boids::drawTrail(sf::RenderWindow &window)
{
    sf::Color tempColor = color;
    // tempColor.a = 20;
    for (int i = 0; i < history.size(); i++)
    {
        sf::CircleShape temp(2);
        tempColor.a = i + 2;
        temp.setFillColor(tempColor);
        temp.setPosition(history[i].x, history[i].y+2);
        window.draw(temp);
    }
}
void Boids::slowDown(float value)
{
    acceleration.x *= value;
    acceleration.y *= value;
}

void Boids::updateVelocity()
{
    velocity.x += acceleration.x;
    velocity.y += acceleration.y;
}
void Boids::limitVelocity(float maxValue)
{

    double size = magnitude(velocity);
    if (size > maxValue)
    {
        velocity.x /= size;
        velocity.y /= size;
    }
}

void Boids::updatePosition()
{
    if (history.size() > 25)
        history.erase(history.begin());
    history.push_back(sf::Vector2f(position.x, position.y));
    position.x += velocity.x;
    position.y += velocity.y;
}

void Boids::checkBoundry()
{
    //left right
    if (position.x > outerBoxRight)
        position.x = outerBoxLeft;
    if (position.x < outerBoxLeft)
        position.x = outerBoxRight;

    //top bottom
    if (position.y > outerBoxRight)
        position.y = outerBoxLeft;
    if (position.y < outerBoxLeft)
        position.y = outerBoxRight;
}

void Boids::applyForce(const sf::Vector2f &force)
{
    acceleration.x += force.x;
    acceleration.y += force.y;
}

sf::Vector2f Boids::separation(std::vector<sf::Vector2f> seperationDiff, int count, float power)
{
    sf::Vector2f steer;
    for (int i = 0; i < seperationDiff.size(); i++)
    {
        steer.x += seperationDiff[i].x;
        steer.y += seperationDiff[i].y;
    }

    steer.x /= count;
    steer.y /= count;

    normalize(steer);
    steer.x *= 5;
    steer.y *= 5;
    steer.x -= velocity.x;
    steer.y -= velocity.y;
    steer.x *= power;
    steer.y *= power;
    limit(steer, 7);
    return steer;
}
sf::Vector2f Boids::alignment(sf::Vector2f sum, int count, float power)
{

    sum.x /= count;
    sum.y /= count;

    sum.x *= 5; // Multiply by maxSpeed
    sum.y *= 5; // Multiply by maxSpeed

    sf::Vector2f steer;
    steer.x = sum.x - velocity.x;
    steer.y = sum.y - velocity.y;

    steer.x *= power;
    steer.y *= power;

    limit(steer, 7);
    return steer;
}
sf::Vector2f Boids::cohesion(sf::Vector2f sum, int count, float power)
{

    sum.x /= count;
    sum.y /= count;

    sf::Vector2f desired;
    desired.x = sum.x - position.x;
    desired.y = sum.y - position.y;

    //normalize(desired);
    desired.x *= 5;
    desired.y *= 5;

    desired.x -= velocity.x;
    desired.y -= velocity.y;

    desired.x *= power;
    desired.y *= power;

    limit(desired, 7);
    return desired;
}

float Boids::findDistance(const sf::Vector2f &v)
{
    float dx = position.x - v.x;
    float dy = position.y - v.y;
    float dist = sqrt(dx * dx + dy * dy);
    return dist;
}

float Boids::magnitude(sf::Vector2f &v)
{
    return sqrt(v.x * v.x + v.y * v.y);
}

void Boids::normalize(sf::Vector2f &v)
{
    float m = magnitude(v);

    if (m > 0)
    {
        v.x /= m;
        v.y /= m;
    }
}

void Boids::limit(sf::Vector2f &v, double max)
{
    double size = magnitude(v);

    if (size > max)
    {
        v.x /= size;
        v.y /= size;
    }
}

float Boids::angle(sf::Vector2f &v)
{
    // From the definition of the dot product
    float angle = (float)(atan2(v.x, -v.y) * 180 / PI);
    return angle;
}