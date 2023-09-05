#pragma once
#include<iostream>
#include"Compound.hpp"

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
	reactant(double reactantMassVolume, const char* reactantMassVolumeUnit, compound* comp, float reactantEquivalents);

	// setter methods
	int setMV(double reactantMassVolume, const char* reactantMassVolumeUnit);
	int setMoles(double mw);
	int setEquivalents(float reactantEquivalents);

	int setReactant(double reactantMV, const char* reactantMassVolumeUnit, compound* comp, float reactantEquivalents);

	int userSetReactant(compound* comp);

	// getter methods
	double getMV();
	double getMol();
};

// Creators

reactant::reactant()
{
	mv = -1.0;
	mvu = "NULL";
	
	mol = -1.0;
	mmol = -1.0;
	
	eq = -1.0;
}

reactant::reactant(double reactantMassVolume, const char* reactantMassVolumeUnit, compound* comp, float reactantEquivalents)
{
	mv = reactantMassVolume;
	mvu = reactantMassVolumeUnit;
	
	setMoles(comp->getMW());
	
	eq = reactantEquivalents;
}

// Setter Methods

int reactant::setMV(double reactantMassVolume, const char* reactantMassVolumeUnit)
{
	mv = reactantMassVolume;
	mvu = reactantMassVolumeUnit;

	return 0;
}

int reactant::setMoles(double mw)
{
	mol = mv / mw;
	mmol = mol * 1000;

	return 0;
}

int reactant::setEquivalents(float reactantEquivalents)
{
	eq = reactantEquivalents;

	return 0;
}

int reactant::setReactant(double reactantMV, const char* reactantMassVolumeUnit, compound* comp, float reactantEquivalents)
{
	mv = reactantMV;
	mvu = reactantMassVolumeUnit;

	setMoles(comp->getMW());

	eq = reactantEquivalents;

	return 0;
}

int reactant::userSetReactant(compound* comp)
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

	setReactant(reactantMV, reactantMassVolumeUnit, comp, reactantEquivalents);
	
	return 0;
}

// Getter Methods

double reactant::getMV()
{
	return mv;
}

double reactant::getMol()
{
	return mol;
}
