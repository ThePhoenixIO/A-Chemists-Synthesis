#pragma once
#include"Compound.hpp"
#include"Reactant.hpp"
#include"StartingMaterial.hpp"

class reagent : public compound, public reactant
{
public:
	reagent();
	reagent(const char* reagentName, const char* reagentFormula, double reagentMW);
	reagent(const char* reagentName, const char* reagentFormula, double reagentMW, 
		startingMaterial* sm, float reagentEquivalance, const char* massVolumeUnits = "g");

	int setReagent(const char* massVolumeUnits, float reagentEquivalance, startingMaterial* sm);
};

reagent::reagent()
{
	setCompound("UNDEFINED", "UNDEFINED", -1);
	setReactant(-1, "UNDEFINED", -1, -1);
}

reagent::reagent(const char* reagentName, const char* reagentFormula, double reagentMW)
{
	setCompound(reagentName, reagentFormula, reagentMW);
}

reagent::reagent(const char* reagentName, const char* reagentFormula, double reagentMW, 
	startingMaterial* sm, float reagentEquivalance, const char* massVolumeUnits = "g")
{
	setCompound(reagentName, reagentFormula, reagentMW);
	setReagent(massVolumeUnits, reagentEquivalance, sm);
}

int reagent::setReagent(const char* massVolumeUnits, float reagentEquivalance, startingMaterial* sm)
{
	this->eq = reagentEquivalance;
	setMol(sm->getMol() * reagentEquivalance);

	this->mv = mol * molecularWeight;
	this->mvu = massVolumeUnits;

	return 0;
}