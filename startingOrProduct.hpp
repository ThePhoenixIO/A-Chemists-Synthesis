#pragma once
//#include"Reagent.hpp"
#include"Reactant.hpp"

#ifndef STARTINGORPRODUCT
#define STARTINGORPRODUCT

class startingOrProduct : public reactant
{
public:
    // constructors
    startingOrProduct();
    startingOrProduct(compound* sop);
    startingOrProduct(compound* sop, double sopMV, const char* sopMVU);

    // setter methods
    int calculateProcuct(double mol, const char* mvuInput);

    // getter methods
	double getMV();
	const char* getMVU();

	double getMol();
	double getMMol();

	float getEquivalents();
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

// Setter Methods
int startingOrProduct::calculateProcuct(double mol, const char* mvuInput)
{
    setMol(mol);
    this->mvu = mvuInput;
    this->mv = mol * baseCompound->getMW();

    return 0;
}

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

#endif // !STARTINGORPRODUCT