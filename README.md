# Boids Army
```
g++ -c -g simulation.cpp && g++ -c -g boids.cpp && g++ -c -o main.o main.cpp && g++ -g simulation.o boids.o main.o -o boids-sim -lsfml-graphics -lsfml-window -lsfml-system && ./boids-sim <windowWidth> <windowHeight> <numBoids>
```