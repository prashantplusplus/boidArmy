#include <iostream>
#include <cuda.h>
#include "boidsGPU.h"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"


void boidsGPU(std::vector<Boids> &boidsObj,sf::RenderWindow& window){
    int blockSize = 256;
    int totalBoids = boidsObj.size();
    int numBlocks = (totalBoids + blockSize - 1) / blockSize;
    int maxBoids = 10000;

    //memory allocate 
    float *boid;
    float *ax,*ay;//xy accelerations of each boid
    cudaMallocManaged(&boid,totalBoids*sizeof(float));
    cudaMallocManaged(&ax,totalBoids*sizeof(float));
    cudaMallocManaged(&ay,totalBoids*sizeof(float));

    initBoidIDs <<< numBlocks, blockSize >>> (boidsObj, boid,maxBoids);
    calculateForcesGPU <<< numBlocks, blockSize >>> (ax,ay);
    //calculateforces
    //update()
}

__global__ void initBoidIDs(std::vector<Boids> &boidsObj, float *boids,int maxBoids) {
    int i = (blockIdx.x * blockDim.x) + threadIdx.x;
    if (i >= maxBoids) return;
    boids[i] = i;
}
__global__ 
void calculateForcesGPU(float *ax, float *ay){

}