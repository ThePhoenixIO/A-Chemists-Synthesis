#pragma once
#include<iostream>
#include<fstream>
#include<unordered_map>

#include"tinyxml2/tinyxml2.h"

#ifndef COMPOUND
#define COMPOUND
// Compiler toggle for setters
#define SETTERS false

/*
* Compound Class
* Independet from reactions
* Used to store common information about compounds
* Accessable through 2 maps
* 1. Common Compound Map [commonCompoundMap] - Only used for common compounds loaded at startup from file	
* 2. Synthesis Compound Map [compoundMap]
*/
class compound
{
protected:
	// Compound Attributes
    const char* name;
    const char* formula;
    double molecularWeight;
	
public:
	// Constructors
    compound();
	compound(const char* compoundName, const char* compoundFormula, double compoundMW);
    
    // Setter methods (if needed)
	#if SETTERS
	int setName(const char* compoundName);
	int setFormula(const char* compoundFormula);
	int setMW(double compoundMW);
	#endif // SETTERS
	
	// Method for setting all attributes at once
    int setCompound(const char* compoundName, const char* compoundFormula, double compoundMW);
	
	// Method for setting all attributes at once from user input
	int userSetCompound();

	// getter methods
	const char* getName();
	const char* getFormula();
	double getMW();

	// XML Method
	int saveToXML(tinyxml2::XMLDocument* doc, tinyxml2::XMLElement* baseNode);
};

// Constructors

/*
* Constructor: compound - Default
* Arguments: none
* Warnings: Hardcoded values [UNDEFINED and -1.0]
* Descriptiom: Default constructor for compound class
* Returns: none
*/
compound::compound()
{
    this->name = "UNDEFINED";
    this->formula = "UNDEFINED";
	this->molecularWeight = -1.0;
}

/*
* Constructor: compound - Primary
* Arguments: const char* compoundName, const char* compoundFormula, double compoundMW
* Warnings: none
* Descriptiom: constructor for compound class
* Returns: none
*/
compound::compound(const char* compoundName, const char* compoundFormula, double compoundMW)
{
	this->name = compoundName;
	this->formula = compoundFormula;
	this->molecularWeight = compoundMW;
}

/*
* Setter Methods
* WARNING CHECK TOGGLE IF NEEDED
*/
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

/*
* Method: setCompound
* Arguments: const char* compoundName, const char* compoundFormula, double compoundMW
* Warnings: comoundFormula default value is "UNDEFINED", compoundMW default value is -1
* Descriptiom: method for setting all attributes at once
* Returns: 0 on success
*/
int compound::setCompound(const char* compoundName, const char* compoundFormula = "UNDEFINED", double compoundMW = -1)
{
	this->name = compoundName;
	this->formula = compoundFormula;
	this->molecularWeight = compoundMW;
    
	return 0;
}

/*
* Method: userSetCompound
* Arguments: none
* Warnings: Buffer overflow possible
* Descriptiom: method for setting all attributes at once from user input
* Returns: 0 on success
* 
* Todo: add buffer overflow protection
* Todo: add compile time allocation of buffer
* Todo: add return codes
*/
int compound::userSetCompound()
{
	// creates variables for user input
	// Warning: buffer overflow possible
	// Buffer limit set to 100
	// TODO: add compile time allocation of buffer
	// TODO: add buffer overflow protection
	char compoundName[100];
	char compoundFormula[100];
	double compoundMolarMass;

	// Prompts the user to set the attributes of the compound
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

/*
* Method: getName
* Arguments: none
* Warnings: none
* Descriptiom: method for getting compound name
* Returns: const char* name
*/
const char* compound::getName()
{
	return this->name;
}

/*
* Method: getFormula
* Arguments: none
* Warnings: none
* Descriptiom: method for getting compound formula
* Returns: const char* formula
*/
const char* compound::getFormula()
{
	return this->formula;
}

/*
* Method: getMW
* Arguments: none
* Warnings: none
* Descriptiom: method for getting compound molecular weight
* Returns: double molecularWeight\
*/
double compound::getMW()
{
	return this->molecularWeight;
}

/*
* Method: saveToXML
* Arguments: tinyxml2::XMLDocument* doc, tinyxml2::XMLElement* baseNode
* Warnings: none
* Descriptiom: method for saving compound to XML map given a base node
* Returns: 0 on success
* Todo: add return codes
*/
int compound::saveToXML(tinyxml2::XMLDocument* doc, tinyxml2::XMLElement* baseNode)
{
	// Create compound node
	tinyxml2::XMLElement* xmlCompound = doc->NewElement("compound");

	// Create, set, and insert name element
	tinyxml2::XMLElement* name = doc->NewElement("name");
	name->SetAttribute("type", "string");
	name->SetText(this->getName());
	xmlCompound->InsertFirstChild(name);

	// Create, set, and insert formula element
	tinyxml2::XMLElement* formula = doc->NewElement("formula");
	formula->SetAttribute("type", "string");
	formula->SetText(this->getFormula());
	xmlCompound->InsertEndChild(formula);

	// Create, set, and insert molecular weight element
	tinyxml2::XMLElement* molecularWeight = doc->NewElement("molecular_weight");
	molecularWeight->SetAttribute("type", "double");
	molecularWeight->SetText(this->getMW());
	xmlCompound->InsertEndChild(molecularWeight);

	// Insert compound node into base node
	baseNode->InsertEndChild(xmlCompound);
	
	return 0;
}

/*
* Function: writeCompoundXML
* Arguments: const char* path, std::unordered_map<const char*, compound*>* map
* Warnings: map is a pointer!!!
* Descriptiom: function for writing compound map to XML file
* Returns: 0 on success
* Todo: add return codes
* Todo: add error handling
* Todo: check and make path
*/
int writeCompoundXML(const char* path, std::unordered_map<const char*, compound*>* map) {
	// Create XML document
	tinyxml2::XMLDocument compoundMap;

	// Create and insert declaration
	compoundMap.InsertFirstChild(compoundMap.NewDeclaration("xml version=\"1.0\" encoding=\"UTF-8\""));
	
	// Create and insert base node
	tinyxml2::XMLElement* xmlCompoundMap = compoundMap.NewElement("compound_map");

	//Take this code, compound code, and common compound code and combine to single compound method to return
	// element node pre constructed
	
	/* TODO List
	* take this code combine with similar code elseware and make single function
	*/

	// initialize iterator [it]
	auto it = map->begin();
	tinyxml2::XMLElement* name = nullptr;
	tinyxml2::XMLElement* formula = nullptr;
	tinyxml2::XMLElement* molecularWeight = nullptr;
	for (int n = 0; n < map->size(); n++, it++)
	{
		compound* comp = it->second;
		tinyxml2::XMLNode* xmlCompound = compoundMap.NewElement("compound");

		// Create, set, and insert name element
		name = compoundMap.NewElement("name");
		name->SetAttribute("type", "string");
		name->SetText(comp->getName());
		xmlCompound->InsertFirstChild(name);

		// Create, set, and insert formula element
		formula = compoundMap.NewElement("formula");
		formula->SetAttribute("type", "string");
		formula->SetText(comp->getFormula());
		xmlCompound->InsertEndChild(formula);

		// Create, set, and insert molecular weight element
		molecularWeight = compoundMap.NewElement("molecular_weight");
		molecularWeight->SetAttribute("type", "double");
		molecularWeight->SetText(comp->getMW());
		xmlCompound->InsertEndChild(molecularWeight);

		xmlCompoundMap->InsertEndChild(xmlCompound);
	}

	// Insert base node into document
	compoundMap.InsertEndChild(xmlCompoundMap);
	compoundMap.SaveFile(path);

	return 0;
}
#endif // !COMPOUND