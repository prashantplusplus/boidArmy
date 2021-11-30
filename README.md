# Boids Army

![Flocking Simulation with Grid Pruning](images/cpuBoids.gif)
###### CPU Simulation with 300 boids

<br />
<br />

```
g++ -c -g simulation.cpp && 
g++ -c -g boids.cpp && 
nvcc -c -g boidsGPU.cu && 
g++ -c -o main.o main.cpp && 
g++ -g simulation.o boids.o boidsGPU.o main.o -o boids-sim -lsfml-graphics -lsfml-window -lsfml-system && 
./boids-sim <windowWidth> <windowHeight> <numBoids>
```




