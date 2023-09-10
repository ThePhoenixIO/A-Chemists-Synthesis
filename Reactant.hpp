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
	reactant(double reactantMassVolume, const char* reactantMassVolumeUnit, double mw, float reactantEquivalents);

	// setter methods
	int setMV(double reactantMassVolume, const char* reactantMassVolumeUnit);
	int setMol(double moles);
	int setEquivalents(float reactantEquivalents);

	int setReactant(double reactantMV, const char* reactantMassVolumeUnit, double mw, float reactantEquivalents);

	int userSetReactant(double mw);

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
	this->mv = -1.0;
	this->mvu = "NULL";
	
	this->mol = -1.0;
	this->mmol = -1.0;
	
	this->eq = -1.0;
}

reactant::reactant(double reactantMassVolume, const char* reactantMassVolumeUnit, double mw, float reactantEquivalents)
{
	this->mv = reactantMassVolume;
	this->mvu = reactantMassVolumeUnit;
	
	setMol(mv / mw);
	
	this->eq = reactantEquivalents;
}

// Setter Methods

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

int reactant::setReactant(double reactantMV, const char* reactantMassVolumeUnit, double mw, float reactantEquivalents)
{
	this->mv = reactantMV;
	this->mvu = reactantMassVolumeUnit;

	setMol(mv / mw);

	this->eq = reactantEquivalents;

	return 0;
}

int reactant::userSetReactant(double mw)
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

	setReactant(reactantMV, reactantMassVolumeUnit, mw, reactantEquivalents);
	
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
