#include <iostream>
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

class Simulation {
    public:
        Simulation(int window_width, int window_height,int count);
        void run();
    private:
        sf::RenderWindow window;
        std::vector<sf::CircleShape> boids;
        std::vector<sf::Vector2f> boidsV;
        int window_width;
        int window_height;
        int boidsCount;
};