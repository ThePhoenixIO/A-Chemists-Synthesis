#pragma once

class compound
{
protected:
    const char* name;
    const char* formula;
    double molarMass;
	
public:
    compound();
	compound(const char* compoundName, const char* compoundFormula, double compoundMolarMass);
    
    // setter methods
	int setName(const char* compoundName);
	int setFormula(const char* compoundFormula);
	int setMolarMass(double compoundMolarMass);
	
    int setCompound(const char* compoundName, const char* compoundFormula = "UNDEFINED", double compoundMolarMass = -1);
};

compound::compound()
{
    name = "UNDEFINED";
    formula = "UNDEFINED";
    molarMass = -1.0;
}

compound::compound(const char* compoundName, const char* compoundFormula, double compoundMolarMass)
{
	name = compoundName;
	formula = compoundFormula;
	molarMass = compoundMolarMass;
}

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

int compound::setMolarMass(double compoundMolarMass)
{
	molarMass = compoundMolarMass;
	
	return 0;
}

int compound::setCompound(const char* compoundName, const char* compoundFormula = "UNDEFINED", double compoundMolarMass = -1)
{
	name = compoundName;
	formula = compoundFormula;
	molarMass = compoundMolarMass;
    
	return 0;
}