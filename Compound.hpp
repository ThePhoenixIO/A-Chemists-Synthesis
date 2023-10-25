#pragma once
#include<iostream>

#ifndef COMPOUND
#define COMPOUND

class compound
{
protected:
    const char* name;
    const char* formula;
    double molecularWeight;
	
public:
    compound();
	compound(const char* compoundName, const char* compoundFormula, double compoundMW);
    
    // setter methods
	/*
	int setName(const char* compoundName);
	int setFormula(const char* compoundFormula);
	int setMW(double compoundMW);
	*/
	
    int setCompound(const char* compoundName, const char* compoundFormula, double compoundMW);

	int userSetCompound();

	// getter methods
	const char* getName();
	const char* getFormula();
	double getMW();
};

// Constructors

compound::compound()
{
    this->name = "UNDEFINED";
    this->formula = "UNDEFINED";
	this->molecularWeight = -1.0;
}

compound::compound(const char* compoundName, const char* compoundFormula, double compoundMW)
{
	this->name = compoundName;
	this->formula = compoundFormula;
	this->molecularWeight = compoundMW;
}

// Setter Methods
/* Methods for setting individual attributes
int compound::setName(const char* compoundName)
{
	name = compoundName;

	return 0;
}

int compound::setFormula(const char* compoundFormula)
{
	formula = compoundFormula;

	return 0;
}

int compound::setMW(double compoundMW)
{
	molecularWeight = compoundMW;
	
	return 0;
}
*/

int compound::setCompound(const char* compoundName, const char* compoundFormula = "UNDEFINED", double compoundMW = -1)
{
	this->name = compoundName;
	this->formula = compoundFormula;
	this->molecularWeight = compoundMW;
    
	return 0;
}

int compound::userSetCompound()
{
	char compoundName[100];
	char compoundFormula[100];
	double compoundMolarMass;

	std::cout << "Enter the name of the compound: ";
	std::cin >> compoundName;

	std::cout << "Enter the formula of the compound: ";
	std::cin >> compoundFormula;

	std::cout << "Enter the molar mass of the compound: ";
	std::cin >> compoundMolarMass;

	setCompound(compoundName, compoundFormula, compoundMolarMass);

	return 0;
}

// Getter Methods

const char* compound::getName()
{
	return this->name;
}

const char* compound::getFormula()
{
	return this->formula;
}

double compound::getMW()
{
	return this->molecularWeight;
}

#endif // !COMPOUND