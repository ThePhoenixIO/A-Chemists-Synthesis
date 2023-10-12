#pragma once
#include"Reactant.hpp"
#include"startingOrProduct.hpp"

#ifndef REAGENT
#define REAGENT

class reagent : public reactant
{
public:
	reagent();
	reagent(compound* baseCompound);
	reagent(compound* baseCompound, startingOrProduct* sop, float reagentEquivalance, const char* massVolumeUnits);

	int setReagent(startingOrProduct* sop, const char* massVolumeUnits, float reagentEquivalance);
};

reagent::reagent()
{
	setReactant(nullptr, -1, "UNDEFINED", -1);
}

reagent::reagent(compound* baseCompound)
{
	setCompound(baseCompound);
}

reagent::reagent(compound* baseCompound, startingOrProduct* sop, float reagentEquivalance, const char* massVolumeUnits)
{
	setCompound(baseCompound);
	setReagent(sop, massVolumeUnits, reagentEquivalance);
}

int reagent::setReagent(startingOrProduct* sop, const char* massVolumeUnits, float reagentEquivalance)
{
	this->eq = reagentEquivalance;
	setMol(sop->getMol() * reagentEquivalance);

	this->mv = mol * baseCompound->getMW();
	this->mvu = massVolumeUnits;

	return 0;
}
#endif // !REAGENT