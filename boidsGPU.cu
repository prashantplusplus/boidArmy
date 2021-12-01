#include <iostream>
#include <cuda.h>
#include "boidsGPU.h"
#include "boids.h"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"


__host__ void boidsGPU(std::vector<Boids> &boidsObj,sf::RenderWindow& window){
    int blockSize = 256;
    int totalBoids = boidsObj.size();
    int numBlocks = (totalBoids + blockSize - 1) / blockSize;
    int maxBoids = 10000;

    //memory allocate 
    float *boid;
    float *px,*py;//xy accelerations of each boid
    float *vx,*vy;//xy accelerations of each boid
    float *ax,*ay;//xy accelerations of each boid

    //copy values from boidsObj to the 
    
    cudaMallocManaged(&boid,totalBoids*sizeof(float));
    cudaMallocManaged(&px,totalBoids*sizeof(float));
    cudaMallocManaged(&py,totalBoids*sizeof(float));
    cudaMallocManaged(&vx,totalBoids*sizeof(float));
    cudaMallocManaged(&vy,totalBoids*sizeof(float));
    cudaMallocManaged(&ax,totalBoids*sizeof(float));
    cudaMallocManaged(&ay,totalBoids*sizeof(float));

    for(int i=0;i<totalBoids;i++){
        px[i] = boidsObj[i].getPosition().x;
        py[i] = boidsObj[i].getPosition().y;
        vx[i] = boidsObj[i].getVelocity().x;
        vy[i] = boidsObj[i].getVelocity().y;
        px[i] = boidsObj[i].getAcceleration().x;
        px[i] = boidsObj[i].getAcceleration().y;
    }

    initBoidIDs <<< numBlocks, blockSize >>> (boidsObj, boid,maxBoids);
    calculateForcesGPU <<< numBlocks, blockSize >>> (px,py,vx,vy,ax,ay,boid);
}

__global__ void initBoidIDs(std::vector<Boids> &boidsObj, float *boids,int maxBoids) {
    int i = (blockIdx.x * blockDim.x) + threadIdx.x;
    if (i >= maxBoids) return;
    boids[i] = i;
}
__global__ void calculateForcesGPU(float *px, float *py, float *vx, float *vy, float *ax, float *ay, float *boid){
    // 3 forces
    //alignment
    //cohesion
    //seperation
    //increment accel using above forces
    //append accel to velo
    //append velo to posi
    //draw using posi

    int i = (blockIdx.x * blockDim.x) + threadIdx.x;

}