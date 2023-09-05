#pragma once
#include "Compound.hpp"
#include "Reactant.hpp"

class startingMaterial : public compound, public reactant
{
public:
	startingMaterial(const char* smName, const char* smFormula, double smMW, double smMV, const char* smMVU);

private:

};

startingMaterial::startingMaterial(const char* smName, const char* smFormula, double smMW, double smMV, const char* smMVU)
{
	setCompound(smName, smFormula, smMW);
	setReactant(smMV, smMVU, getMW(), 1);
}
