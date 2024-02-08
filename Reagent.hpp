#pragma once
#include"Reactant.hpp"
#include"startingOrProduct.hpp"

#ifndef REAGENT
#define REAGENT

/*
* reagent class
* reaction dependent
* This class is used to store the reagent information for a specific reaction
* This class is a child of the reactant class which holds its protected variables
* This class is the counterpart of the startingOrProduct
* Accessable through:
* 1. The reaction that it is a part of
*/
class reagent : public reactant
{
public:
	//Constructors
	reagent();
	reagent(compound* baseCompound);
	reagent(compound* baseCompound, startingOrProduct* sop, float reagentEquivalance, const char* massVolumeUnits);

	//Setters
	int setReagent(startingOrProduct* sop, const char* massVolumeUnits, float reagentEquivalance);

	// Caluclations
	void calculateReagent(startingOrProduct* sm);
};
//Constructors

/*
* Constructor: reagent - default
* Arguments: None
* Warnings: Default values [nullptr, -1, "UNDEFINED", -1]
* Description: Default constructor for the reagent class
* Returns: None
*/
reagent::reagent()
{
	setReactant(nullptr, -1, "UNDEFINED", -1);
}

/*
* Constructor: reagent - baseCompound
* Arguments: compound* baseCompound
* Warnings: Default values (implicit through reactant constructor)
* Description: Constructor for the reagent class with given baseCompound
* Returns: None
*/
reagent::reagent(compound* baseCompound)
{
	setCompound(baseCompound);
}

/*
* Constructor: reagent - all info
* Arguments: compound* baseCompound, startingOrProduct* sop, float reagentEquivalance, const char* massVolumeUnits
* Warnings: None
* Description: Constructor for the reagent class with given baseCompound, startingOrProduct, reagentEquivalance, and massVolumeUnits
* Returns: None
*/
reagent::reagent(compound* baseCompound, startingOrProduct* sop, float reagentEquivalance, const char* massVolumeUnits)
{
	setCompound(baseCompound);
	setReagent(sop, massVolumeUnits, reagentEquivalance);
}

// Is this function necessary?
/*
* Method: setReagent
* Arguments: startingOrProduct* sop, const char* massVolumeUnits, float reagentEquivalance
* Warnings: None
* Description: Sets the values for the reagent class
* Returns: 0 if successful
*/
int reagent::setReagent(startingOrProduct* sop, const char* massVolumeUnits, float reagentEquivalance)
{
	this->eq = reagentEquivalance;
	setMol(sop->getMol() * reagentEquivalance);

	this->mv = mol * baseCompound->getMW();
	this->mvu = massVolumeUnits;

	return 0;
}

/*
* Method: calculateReagent
* Arguments[sm = starting material]: startingOrProduct* sm
* Warnings: None
* Description: Calculates the reagent values
* Returns: None
*/
void reagent::calculateReagent(startingOrProduct* sm)
{
	setMol((sm->getMol() * this->eq));
	this->mv = mol * baseCompound->getMW();
}
#endif // !REAGENT