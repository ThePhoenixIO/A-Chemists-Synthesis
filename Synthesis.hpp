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

    reaction* product;

    void addStartingPoint(reaction* r);

    void setProduct(reaction* r);

    int calculateSynthesis();
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
}

void synthesis::setProduct(reaction* r)
{
    product = r;
}

int synthesis::calculateSynthesis()
{
    
}

#endif // !SYNTHESIS