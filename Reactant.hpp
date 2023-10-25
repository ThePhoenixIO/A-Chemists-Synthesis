#pragma once
#include<iostream>
#include "Compound.hpp"
#include"CommonCompounds.hpp"

#ifndef REACTANT
#define REACTANT

class reactant
{
protected:
	double mv;
	const char* mvu;

	double mol;
	double mmol;
	float eq;

public:
	reactant();
	reactant (compound* compoundInput);
	reactant(compound* compoundInput, double reactantMassVolume, const char* reactantMassVolumeUnit, float reactantEquivalents);

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

reactant::reactant()
{
	this->baseCompound = nullptr;

	this->mv = -1.0;
	this->mvu = "NULL";
	
	this->mol = -1.0;
	this->mmol = -1.0;
	
	this->eq = -1.0;
}

reactant::reactant(compound* compoundInput)
{
	this->baseCompound = compoundInput;

	this->mv = -1.0;
	this->mvu = "NULL";
	
	this->mol = -1.0;
	this->mmol = -1.0;
	
	this->eq = -1.0;
}

reactant::reactant(compound* compoundInput, double reactantMassVolume, const char* reactantMassVolumeUnit, float reactantEquivalents)
{
	this->baseCompound = compoundInput;

	this->mv = reactantMassVolume;
	this->mvu = reactantMassVolumeUnit;
	
	setMol(mv / baseCompound->getMW());
	
	this->eq = reactantEquivalents;
}

// Setter Methods
int reactant::setCompound(compound* compoundInput)
{
	this->baseCompound = compoundInput;

	return 0;
}

int reactant::setMV(double reactantMassVolume, const char* reactantMassVolumeUnit)
{
	this->mv = reactantMassVolume;
	this->mvu = reactantMassVolumeUnit;

	return 0;
}

int reactant::setMol(double moles)
{
	this->mol = moles;
	this->mmol = mol * 1000;

	return 0;
}

int reactant::setEquivalents(float reactantEquivalents)
{
	this->eq = reactantEquivalents;

	return 0;
}

int reactant::setReactant(compound* compoundInput, double reactantMV, const char* reactantMassVolumeUnit, float reactantEquivalents)
{
	this->baseCompound = compoundInput;

	this->mv = reactantMV;
	this->mvu = reactantMassVolumeUnit;

	setMol(mv / baseCompound->getMW());

	this->eq = reactantEquivalents;

	return 0;
}

int reactant::userSetReactant(compound* compoundInput)
{
	double reactantMV;
	char reactantMassVolumeUnit[100];
	float reactantEquivalents;

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

double reactant::getMV()
{
	return this->mv;
}

const char* reactant::getMVU()
{
	return this->mvu;
}

double reactant::getMol()
{
	return this->mol;
}

double reactant::getMMol()
{
	return this->mmol;
}

float reactant::getEquivalents()
{
	return this->eq;
}

#endif // !REACTANT