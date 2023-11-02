#pragma once
//#include <vector>
#include "Reaction.hpp"

#ifndef SYNTHESIS
#define SYNTHESIS

class synthesis
{
public:
    synthesis();

    synthesis(reaction* p);

    std::vector<reaction*> startingPoints;
    int numStartingPoints = 0;

    reaction* product;

    void addStartingPoint(reaction* r);

    void setProduct(reaction* r);

    // acceptible directions are "forward (f)" and "reverse (r)"
    int calculateSynthesis(const char* direction = "forward");

    //xml tree
};

synthesis::synthesis()
{
    startingPoints = std::vector<reaction*>();
    product = nullptr;
}

synthesis::synthesis(reaction* p)
{
    startingPoints = std::vector<reaction*>();
    product = p;
}

void synthesis::addStartingPoint(reaction* r)
{
    startingPoints.insert(startingPoints.end(), r);
    numStartingPoints++;
}

void synthesis::setProduct(reaction* r)
{
    product = r;
}

int synthesis::calculateSynthesis(const char* direction)
{
    if(direction == "forward" || direction == "f")
    {
        return 0;
    }
    else if(direction == "reverse" || direction == "r")
    {
        return 0;
    }
    else
    {
        std::cout << "Error: Invalid direction" << std::endl;
        return 1;
    }
}

#endif // !SYNTHESIS