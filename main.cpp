#include <SFML/Graphics.hpp>
#include "simulation.h"
#include "globals.h"
int outerBoxLeft;
int outerBoxRight;
bool cuda;
int main(int argc, char* argv[])
{
    int boidsCount;
    int windowHeight, windowWidth;
    try{
        windowWidth = std::stoi(std::string(argv[1]));
        windowHeight = std::stoi(std::string(argv[2]));
        boidsCount = std::stoi(std::string(argv[3]));

        if(argc == 5){
            if(std::string(argv[4]) == "gpu")
                cuda = true;
            else
                cuda = false;
        }
        else{
            cuda = false;
        }

        outerBoxLeft = 20;
        outerBoxRight = windowWidth - 20;
    }
    catch (const std::exception& ex){
        boidsCount = 350;
        windowHeight = 400;
        windowWidth = 400;
        cuda = false;
        outerBoxLeft = 20;
        outerBoxRight = windowWidth - 20;
    }
    Simulation s1(windowWidth,windowHeight,boidsCount);
    s1.run();

    return 0;
}