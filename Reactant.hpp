#pragma once
#include<iostream>
#include "Compound.hpp"
#include"CommonCompounds.hpp"

#ifndef REACTANT
#define REACTANT

/*
* Reactant Class
* Reaction dependent
* Used to store/calculate specific information about a reactant for a specific reaction
* Accessable through
* 1. Reaction Object it was spawned from
*/
class reactant
{
protected:
	// Common Attributes

	// Mass/Volume of the reactant
	double mv;
	// Units of the Mass/Volume of the reactant
	const char* mvu;

	// Moles (used in calculations) and mMoles (displayed) of the reactant
	double mol;
	double mmol;
	
	// Equivalents of the reactant compared to the starting material
	float eq;

public:
	// Constructors
	reactant();
	reactant (compound* compoundInput);
	reactant(compound* compoundInput, double reactantMassVolume, const char* reactantMassVolumeUnit, float reactantEquivalents);

	// Pointer to the compound object that this reactant is based on (common infotmation that is reaction independent)
	compound* baseCompound;

	// setter methods
	int setCompound(compound* compoundInput);
	int setMV(double reactantMassVolume, const char* reactantMassVolumeUnit);
	int setMol(double moles);
	int setEquivalents(float reactantEquivalents);

	int setReactant(compound* compoundInput, double reactantMV, const char* reactantMassVolumeUnit, float reactantEquivalents);

	int userSetReactant(compound* compoundInput);

	// getter methods
	double getMV();
	const char* getMVU();

	double getMol();
	double getMMol();

	float getEquivalents();
};

// Constructors

/*
* Constructor: reactant - Default
* Arguments: None
* Warnings: Hardcoded values [-1.0, "NULL", -1.0, -1.0, -1.0]
* Description: Default constructor for the reactant class
* Returns: None
*/
reactant::reactant()
{
	this->baseCompound = nullptr;

	this->mv = -1.0;
	this->mvu = "NULL";
	
	this->mol = -1.0;
	this->mmol = -1.0;
	
	this->eq = -1.0;
}

/*
* Constructor: reactant - Known Compound; Unknown Mass/Volume or Equivalents
* Arguments: compound* compoundInput
* Warnings: Hardcoded values [-1.0, "NULL", -1.0, -1.0, -1.0]
* Description: Constructor for the reactant class given known compound
* Returns: None
*/
reactant::reactant(compound* compoundInput)
{
	this->baseCompound = compoundInput;

	this->mv = -1.0;
	this->mvu = "NULL";
	
	this->mol = -1.0;
	this->mmol = -1.0;
	
	this->eq = -1.0;
}

/*
* Constructor: reactant - Known Compound; Known Mass/Volume and Equivalents
* Arguments: compound* compoundInput, double reactantMassVolume, const char* reactantMassVolumeUnit, float reactantEquivalents
* Warnings: None
* Returns: None
*/
reactant::reactant(compound* compoundInput, double reactantMassVolume, const char* reactantMassVolumeUnit, float reactantEquivalents)
{
	this->baseCompound = compoundInput;

	this->mv = reactantMassVolume;
	this->mvu = reactantMassVolumeUnit;
	
	// Calculate the moles of the reactant given the mass/volume and the molecular weight of the compound
	setMol(mv / baseCompound->getMW());
	
	this->eq = reactantEquivalents;
}

// Setter Methods
// TODO: Add error checking for the setters
// TODO: Add return codes for the setters

/*
* Method: setCompound
* Arguments: compound* compoundInput
* Warnings: None
* Description: Sets the compound pointer to the compound object that this reactant is based on
* Returns: 0 if successful
*/
int reactant::setCompound(compound* compoundInput)
{
	this->baseCompound = compoundInput;

	return 0;
}

/*
* Method: setMV
* Arguments: double reactantMassVolume, const char* reactantMassVolumeUnit
* Warnings: None
* Description: Sets the mass/volume of the reactant and the units of the mass/volume of the reactant
* Returns: 0 if successful
*/
int reactant::setMV(double reactantMassVolume, const char* reactantMassVolumeUnit)
{
	this->mv = reactantMassVolume;
	this->mvu = reactantMassVolumeUnit;

	return 0;
}

/*
* Method: setMol
* Arguments: double moles
* Warnings: None
* Description: Sets the moles of the reactant and calculates the mMoles of the reactant
* Returns: 0 if successful
*/
int reactant::setMol(double moles)
{
	this->mol = moles;
	this->mmol = mol * 1000;

	return 0;
}

/*
* Method: setEquivalents
* Arguments: float reactantEquivalents
* Warnings: None
* Description: Sets the equivalents of the reactant
* Returns: 0 if successful
*/
int reactant::setEquivalents(float reactantEquivalents)
{
	this->eq = reactantEquivalents;

	return 0;
}

/*
* Method: setReactant
* Arguments: compound* compoundInput, double reactantMV, const char* reactantMassVolumeUnit, float reactantEquivalents
* Warnings: None
* Description: Sets all the attributes of the reactant from the given arguments
* Returns: 0 if successful
*/
int reactant::setReactant(compound* compoundInput, double reactantMV, const char* reactantMassVolumeUnit, float reactantEquivalents)
{
	this->baseCompound = compoundInput;

	this->mv = reactantMV;
	this->mvu = reactantMassVolumeUnit;

	setMol(mv / baseCompound->getMW());

	this->eq = reactantEquivalents;

	return 0;
}

/*
* Method: userSetReactant
* Arguments: compound* compoundInput
* Warnings: Buffer overflow possible
* Description: Prompts the user to set the attributes of the reactant
* Returns: 0 if successful
* 
* ToDo: Add ability for user lookup of compound (includes both maps)
* Todo: add buffer overflow protection
* Todo: add compile time allocation of buffer
* Todo: add return codes
*/
int reactant::userSetReactant(compound* compoundInput)
{
	// creates variables for user input
	// Warning: buffer overflow possible
	// Buffer limit set to 100
	// TODO: add compile time allocation of buffer
	// TODO: add buffer overflow protection

	double reactantMV;
	char reactantMassVolumeUnit[100];
	float reactantEquivalents;

	// Prompts the user to set the attributes of the reactant
	std::cout << "Enter the Mass/Volume of the reactant: ";
	std::cin >> reactantMV;

	std::cout << "Enter the units for the Mass/Volume of the reactant: ";
	std::cin >> reactantMassVolumeUnit;

	std::cout << "Enter the equivalents of the reactant: ";
	std::cin >> reactantEquivalents;

	setReactant(compoundInput, reactantMV, reactantMassVolumeUnit, reactantEquivalents);
	
	return 0;
}

// Getter Methods

/*
* Method: getMV
* Arguments: None
* Warnings: None
* Description: Returns the mass/volume of the reactant
* Returns: double mv
*/
double reactant::getMV()
{
	return this->mv;
}

/*
* Method: getMVU
* Arguments: None
* Warnings: None
* Description: Returns the units of the mass/volume of the reactant
* Returns: const char* mvu
*/
const char* reactant::getMVU()
{
	return this->mvu;
}

/*
* Method: getMol
* Arguments: None
* Warnings: None
* Description: Returns the moles of the reactant
* Returns: double mol
*/
double reactant::getMol()
{
	return this->mol;
}

/*
* Method: getMMol
* Arguments: None
* Warnings: None
* Description: Returns the mMoles of the reactant
* Returns: double mmol
*/
double reactant::getMMol()
{
	return this->mmol;
}

/*
* Method: getEquivalents
* Arguments: None
* Warnings: None
* Description: Returns the equivalents of the reactant
* Returns: float eq
*/
float reactant::getEquivalents()
{
	return this->eq;
}

#endif // !REACTANT