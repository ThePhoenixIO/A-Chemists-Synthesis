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
	bool setName(const char* compoundName);
	bool setFormula(const char* compoundFormula);
	bool setMolarMass(double compoundMolarMass);
	
    bool setCompound(const char* compoundName, const char* compoundFormula = "UNDEFINED", double compoundMolarMass = -1);
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

bool compound::setName(const char* compoundName)
{
	name = compoundName;

	return true;
}

bool compound::setFormula(const char* compoundFormula)
{
	formula = compoundFormula;

	return true;
}

bool compound::setMolarMass(double compoundMolarMass)
{
	molarMass = compoundMolarMass;
	
	return true;
}

bool compound::setCompound(const char* compoundName, const char* compoundFormula = "UNDEFINED", double compoundMolarMass = -1)
{
	name = compoundName;
	formula = compoundFormula;
	molarMass = compoundMolarMass;
    
	return true;
}