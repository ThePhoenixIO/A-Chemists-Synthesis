#pragma once
#include "Compound.hpp"
#include "Reactant.hpp"

#ifndef STARTING_MATERIAL
#define STARTING_MATERIAL

class startingMaterial : public compound, public reactant
{
public:
	startingMaterial();
	startingMaterial(const char* smName, const char* smFormula, double smMW, double smMV, const char* smMVU);

private:

};

startingMaterial::startingMaterial()
{
	setCompound("UNDEFINED", "UNDEFINED", -1);
	setReactant(-1, "UNDEFINED", getMW(), 1);
}

startingMaterial::startingMaterial(const char* smName, const char* smFormula, double smMW, double smMV, const char* smMVU = "g")
{
	setCompound(smName, smFormula, smMW);
	setReactant(smMV, smMVU, getMW(), 1);
}

#endif // !STARTING_MATERIAL