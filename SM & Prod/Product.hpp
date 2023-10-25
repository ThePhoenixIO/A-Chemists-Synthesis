#pragma once
#include "Compound.hpp"
#include "Reactant.hpp"

#ifndef PRODUCT
#define PRODUCT

class product  : public compound, public reactant
{
private:
	// Place holder for percent yield calculation
	float percentYield = 1;

public:
	product();
	product(reactant* startingMaterial);
	product(const char* compoundName, const char* compoundFormula, double compoundMW, 
		reactant* startingMaterial, const char* compoundMVU);

	int setPercentYield(float py);

	int calculateProduct(reactant* startingMaterial);
};

product::product()
{
	setCompound("UNDEFINED", "UNDEFINED", -1);
	setReactant(-1, "UNDEFINED", -1, 1);
}

product::product(reactant* startingMaterial)
{
	this->eq = 1;

	calculateProduct(startingMaterial);
}

product::product(const char* compoundName, const char* compoundFormula, double compoundMW, 
	reactant* startingMaterial, const char* compoundMVU = "g")
{
	setCompound(compoundName, compoundFormula, compoundMW);
	this->mvu = compoundMVU;
	this->eq = 1;

	calculateProduct(startingMaterial);
}

int product::setPercentYield(float py)
{
	this->percentYield = py;

	return 0;
}

int product::calculateProduct(reactant* startingMaterial)
{
	// calculate the product
	double moles = (startingMaterial->getMol() * percentYield);
	setMol(moles);
	this->mv = this->mol * this->molecularWeight;

	return 0;
}

#endif // !PRODUCT