#include <SFML/Graphics.hpp>
#include "simulation.h"
int main(int argc, char* argv[])
{
    int boidsCount;
    int windowHeight, windowWidth;
    try{
        windowWidth = std::stoi(std::string(argv[1]));
        windowHeight = std::stoi(std::string(argv[2]));
        boidsCount = std::stoi(std::string(argv[3]));
    }
    catch (const std::exception& ex){
        boidsCount = 350;
        windowHeight = 400;
        windowWidth = 400;
    }
    Simulation s1(windowWidth,windowHeight,boidsCount);
    s1.run();

    return 0;
}