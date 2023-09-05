#pragma once
#include "Compound.hpp"
#include "Reactant.hpp"

class product  : public compound, public reactant
{
private:
	// Place holder for percent yield calculation
	float percentYield = 1;

public:
	product(reactant* startingMaterial);

	int calculateProduct(reactant* startingMaterial);
};

product::product(reactant* startingMaterial)
{
	setEquivalents(1);

	calculateProduct(startingMaterial);
}

int product::calculateProduct(reactant* startingMaterial)
{
	// calculate the product
	setMoles(startingMaterial->getMol());
	mv = (mol * molecularWeight) * percentYield;

	return 0;
}