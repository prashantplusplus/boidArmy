#include <iostream>
#include <random>
#include "simulation.h"
#include "boids.h"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

Boids::Boids(sf::Color color, sf::Vector2f position, sf::Vector2f velocity){
    this->circle_boid = sf::CircleShape(2);
    circle_boid.setFillColor(color);
    circle_boid.setPosition(position.x, position.y);
    this->color = color;
    this->position = position;
    this->velocity = velocity;
    this->acceleration = sf::Vector2f(0,0);
}

sf::Vector2f Boids::getPosition(){
    return position;
}

sf::Vector2f Boids::getVelocity(){
    return velocity;
}

void Boids::setPositionX(float value){
    position.x = value;
}

void Boids::setPositionY(float value){
    position.x = value;
}

void Boids::setVelocityX(float value){
    velocity.x =  value;
}

void Boids::setVelocityY(float value){
    velocity.y =  value;
}

void Boids::run(std::vector<Boids>& boidsObj,sf::RenderWindow& window){
    sf::Vector2f  alignForce = alignment(boidsObj,0.7);
    // sf::Vector2f  cohesionForce = cohesion(boidsObj);
    // sf::Vector2f  seperationForce = seperation(boidsObj);
    applyForce(alignForce);
    // applyForce(cohesionForce);
    // applyForce(seperationForce);

    update(window);
}

void Boids::update(sf::RenderWindow& window){
    //slowDown(0.9f);
    updateVelocity();
    limitVelocity(5.65);
    updatePosition();
    checkBoundry();
    drawBoid(window);
    drawTrail(window);
}

void Boids::drawBoid(sf::RenderWindow& window){
    circle_boid.setPosition(position.x,position.y);
    window.draw(circle_boid);
}
void Boids::drawTrail(sf::RenderWindow& window){
    sf::Color tempColor = color;
    // tempColor.a = 20;
    for(int i=0;i<history.size();i++){
        sf::CircleShape temp(2);
        tempColor.a = i+2;
        temp.setFillColor(tempColor);
        temp.setPosition(history[i].x, history[i].y);
        window.draw(temp);
    }
}
void Boids::slowDown(float value){
    acceleration.x *= value;
    acceleration.y *= value;
}

void Boids::updateVelocity(){
    velocity.x += acceleration.x;
    velocity.y += acceleration.y;
}
void Boids::limitVelocity(float maxValue){

    double size = sqrt(velocity.x*velocity.x + velocity.y*velocity.y);
    if (size > maxValue) {
        velocity.x /= size;
        velocity.y /= size;
    }
}

void Boids::updatePosition(){
    if(history.size()>30)
        history.erase(history.begin());
    history.push_back(sf::Vector2f(position.x,position.y));
    position.x += velocity.x;
    position.y += velocity.y;
}

void Boids::checkBoundry(){
    // //left right
    // if (position.x > 700-20 || position.x < 20)
    //     velocity.x = -velocity.x;

    // //top bottom
    // if (position.y > 700-20 || position.y < 20)
    //     velocity.y = -velocity.y;


    //left right
    if (position.x > 680)
        position.x = 20;
    if (position.x < 20)
        position.x = 680;

    //top bottom
    if (position.y > 680)
        position.y = 20;
    if (position.y < 20)
        position.y = 680;

}

void Boids::applyForce(const sf::Vector2f& force)
{
    acceleration.x += force.x;
    acceleration.y += force.y;
}

sf::Vector2f Boids::separation(const std::vector<Boids> &boidObj){
    return sf::Vector2f(0,0);
}
sf::Vector2f Boids::alignment(const std::vector<Boids> &boidObj, float power){
    float neighbordist = 80;

    sf::Vector2f sum(0, 0);
    int count = 0;
    for (int i = 0; i < boidObj.size(); i++) {
        float d = findDistance(boidObj[i].position);
        if ((d > 0) && (d < neighbordist)) { // 0 < d < 50
            sum.x += boidObj[i].velocity.x;
            sum.y += boidObj[i].velocity.y;
            count++;
        }
    }
    if (count > 0) {

        sum.x /= count;
        sum.y /= count;
        
        sum.x *= 4;    // Multiply by maxSpeed
        sum.y *= 4;    // Multiply by maxSpeed

        sf::Vector2f steer;
        steer.x = sum.x - velocity.x;
        steer.y = sum.y - velocity.y;

        steer.x *= power;
        steer.y *= power;
        return steer;
    } else{
            sf::Vector2f temp(0, 0);
            return temp;
    }
        
}
sf::Vector2f Boids::cohesion(const std::vector<Boids> &boidObj){
    return sf::Vector2f(0,0);
}

float Boids::findDistance(const sf::Vector2f& v){
    float dx = position.x - v.x;
    float dy = position.y - v.y;
    float dist = sqrt(dx*dx + dy*dy);
    return dist;
}