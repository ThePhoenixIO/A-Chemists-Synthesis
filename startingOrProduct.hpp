#pragma once
#include"Reactant.hpp"

#ifndef STARTINGORPRODUCT
#define STARTINGORPRODUCT

// Debug compiler flag
#define GETTERDEBUGFLAG 0
/*
* startingOrProduct class
* reaction independent
* This class is used to store the starting material or product of a reaction(s)
* This class is a child of the reactant class which holds its protected variables
* Accessable through
* 1. All reaction objects that contain the starting material or product object
*/
class startingOrProduct : public reactant
{
public:
    // constructors
    startingOrProduct();
    startingOrProduct(compound* sop);
    startingOrProduct(compound* sop, double sopMV, const char* sopMVU);

    // setter methods
    int calculateProcuct(double mol, const char* mvuInput);
    #if GETTERDEBUGFLAG
    getter methods
	double getMV();
	//const char* getMVU();

	double getMol();
	double getMMol();

	float getEquivalents();
    #endif // GETTERDEBUGFLAG#endif // GETTERDEBUGFLAG
};

// Constructors
startingOrProduct::startingOrProduct()
{
    setReactant(nullptr, -1, "UNDEFINED", -1);
}

startingOrProduct::startingOrProduct(compound* sop)
{
    setReactant(sop, -1, "UNDEFINED", 1);
}

startingOrProduct::startingOrProduct(compound* sop, double sopMV, const char* sopMVU)
{
    // Assuming eq 1 only works for organic reactions
    setReactant(sop, sopMV, sopMVU, 1);
}

/*
* Method: calculateProcuct
* Arguments[Starting material]: double mol, const char* mvuInput
* Warnings: None
* Description: This method is used to calculate the molecular weight of the product given starting material
* Returns: 0 if successful
* 
* Todo: Add error checking
* Todo: Add return codes
* Todo: Add other fuction with sm input
*/
int startingOrProduct::calculateProcuct(double mol, const char* mvuInput)
{
    setMol(mol);
    this->mvu = mvuInput;
    this->mv = mol * baseCompound->getMW();

    return 0;
}

#if GETTERDEBUGFLAG
// Getter Methods
double startingOrProduct::getMV()
{
	return this->mv;
}

const char* startingOrProduct::getMVU()
{
	return this->mvu;
}

double startingOrProduct::getMol()
{
	return this->mol;
}

double startingOrProduct::getMMol()
{
	return this->mmol;
}

float startingOrProduct::getEquivalents()
{
	return this->eq;
}
#endif // GETTERDEBUGFLAG

#endif // !STARTINGORPRODUCT