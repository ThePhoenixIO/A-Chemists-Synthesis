#pragma once
#include<iostream>
#include<fstream>

#include"tinyxml2/tinyxml2.h"

#ifndef COMPOUND
#define COMPOUND
#define SETTERS false

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
	#if SETTERS
	int setName(const char* compoundName);
	int setFormula(const char* compoundFormula);
	int setMW(double compoundMW);
	#endif // SETTERS
	
    int setCompound(const char* compoundName, const char* compoundFormula, double compoundMW);

	int userSetCompound();

	// getter methods
	const char* getName();
	const char* getFormula();
	double getMW();

	int saveToXML(tinyxml2::XMLDocument* doc, tinyxml2::XMLElement* baseNode);
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

#if SETTERS
//Setter Methods
//Methods for setting individual attributes
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
#endif // SETTERS

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

inline int compound::saveToXML(tinyxml2::XMLDocument* doc, tinyxml2::XMLElement* baseNode)
{
	tinyxml2::XMLElement* xmlCompound = doc->NewElement("compound");

	tinyxml2::XMLElement* name = commonCompoundXML.NewElement("name");
	name->SetAttribute("type", "string");
	name->SetText(this->getName());
	xmlCompound->InsertFirstChild(name);

	tinyxml2::XMLElement* formula = commonCompoundXML.NewElement("formula");
	formula->SetAttribute("type", "string");
	formula->SetText(this->getFormula());
	xmlCompound->InsertEndChild(formula);

	tinyxml2::XMLElement* molecularWeight = commonCompoundXML.NewElement("molecular_weight");
	molecularWeight->SetAttribute("type", "double");
	molecularWeight->SetText(this->getMW());
	xmlCompound->InsertEndChild(molecularWeight);

	baseNode->InsertEndChild(xmlCompound);
}
#endif // !COMPOUND