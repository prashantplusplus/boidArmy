#include <iostream>
#include <vector>
#include <cuda.h>
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"


#ifndef BOID_CU_H_
#define BOID_CU_H_

void boidsGPU(std::vector<Boids> &boidsObj,sf::RenderWindow& window);
void initBoidIDs(std::vector<Boids> &boidsObj, int maxBoids);
void calculateForcesGPU(float *ax, float *ay)


#endif