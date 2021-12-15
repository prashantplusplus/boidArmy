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
    drawBoid(boid,px,py);
}

__global__ void initBoidIDs(std::vector<Boids> &boidsObj, float *boids,int maxBoids) {
    int i = (blockIdx.x * blockDim.x) + threadIdx.x;
    if (i >= maxBoids) return;
    boids[i] = i;
}
__global__ void calculateForcesGPU(float *px, float *py, float *vx, float *vy, float *ax, float *ay, float *boid){
    int i = (blockIdx.x * blockDim.x) + threadIdx.x;

    // 3 forces
    alignment(ax[i],ay[i],sum,count,1.0);
    cohesion(ax[i],ay[i],sum,count,1.0);
    seperation(ax[i],ay[i],sum,count,1.0)

    vx[i] += ax[i];
    vy[i] += ay[i];
    
    px[i] += vx[i];
    py[i] += py[i];
    

}
__global__ void separation(float ax, float ay, int sum, int count, float power)
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
    ax = steer.x;
    ay = steer.y;
}
__global__ void alignment(float *ax, float *ay, int sum, int count, float power)
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
    ax = steer.x;
    ay = steer.y;
}
__global__ void cohesion(float *ax, float *ay, int sum, int count, float power)
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
    ax = desired.x;
    ay = desired.y;
}

void drawBoids(,float *px, float *py){
    for(int i=0;i<totalBoids;i++){
        boids[i] = i;
        sf::CircleShape circle_boid(3);
        circle_boid.setFillColor(color);
        circle_boid.setPosition(px[i], py[i]);
        window.draw(circle_boid);
    }
}