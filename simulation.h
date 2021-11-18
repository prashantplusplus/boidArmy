#include <iostream>
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

class Simulation {
    public:
        Simulation();
        void run();
    private:
        std::vector<sf::CircleShape> c;
};