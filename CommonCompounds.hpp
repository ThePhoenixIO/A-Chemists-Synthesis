#pragma once
#include"Compound.hpp"
#define LOADXML true

std::unordered_map<const char*, compound*> commonCompMap;
tinyxml2::XMLDocument commonCompoundXML;

// Clean up file and remove depricated code

#if LOADXML
/*
* TESTING ONLY DO NOT DEPLOY IN RELEASE
* Function: initMap 
* Arguments: none
* Warnings: Hardcoded values
* Descriptiom: Initializes the map with common compounds
* Returns: none
*/
void initMap() {
    commonCompMap["Boc-Leu-OH"] = new compound("Boc-Leu-OH", "C11H21NO4", 231.292);
    commonCompMap["N,O-dimethylhydroxylamine"] = new compound("N,O-dimethylhydroxylamine", "C8H17NO1", 97.54);
    commonCompMap["EDC"] = new compound("EDC", "C8H17N3", 191.7);
    commonCompMap["HOBt"] = new compound("HOBt", "C6H5N3O", 135.12);
    commonCompMap["DIPEA"] = new compound("DIPEA", "C8H19N", 129.24);
    commonCompMap["Boc-Leu-N(O-CH3)CH3"] = new compound("Boc-Leu-N(O-CH3)CH3", "C13H26N2O4", 274.189);
    commonCompMap["TFA-Leu-N(O-CH3)CH3"] = new compound("TFA-Leu-N(O-CH3)CH3", "C10H18F3N2O3", 271.260);
    commonCompMap["CBZ-Leu-Leu-OH"] = new compound("CBZ-Leu-Leu-OH", "C20H30N2O5", 378.469);
    commonCompMap["CBZ-Leu-Leu-N(O-CH3)CH3"] = new compound("CBZ-Leu-Leu-N(O-CH3)CH3", "C26H46N4O6", 534.698);
}

/*
* Function: saveCommonCompound
* Arguments: tinyxml2::XMLElement* root, compound* comp
* Warnings: none
* Descriptiom: Saves a compound to the common compound XML map
* Returns: none
*/
void saveCommonCompound(tinyxml2::XMLElement* root, compound* comp) {
    // Create XML element
    tinyxml2::XMLNode* xmlCompound = commonCompoundXML.NewElement("compound");
    
    // Create, set, and insert name element
    tinyxml2::XMLElement* name = commonCompoundXML.NewElement("name");
    name->SetAttribute("type", "string");
    name->SetText(comp->getName());
    xmlCompound->InsertFirstChild(name);
    
    // Create, set, and insert formula element
    tinyxml2::XMLElement* formula = commonCompoundXML.NewElement("formula");
    formula->SetAttribute("type", "string");
    formula->SetText(comp->getFormula());
    xmlCompound->InsertEndChild(formula);

    // Create, set, and insert molecular weight element
    tinyxml2::XMLElement* molecularWeight = commonCompoundXML.NewElement("molecular_weight");
    molecularWeight->SetAttribute("type", "double");
    molecularWeight->SetText(comp->getMW());
    xmlCompound->InsertEndChild(molecularWeight);

    // Insert compound into root
    root->InsertEndChild(xmlCompound);
}

/*
* Function: saveCommonCompoundXML
* Arguments: const char* path
* Warnings: none
* Descriptiom: Saves the common compound XML map to specified path
* Returns: none
*/
void saveCommonCompoundXML(const char* path) {
    commonCompoundXML.SaveFile(path);
}

/*
* Function: generateCommonCompound
* Arguments: none
* Warnings: hardcoded values [initMap()]
* Descriptiom: Generates the common compound XML map from the initMap() function
* Returns: none
*/
void generateCommonCompoundFile() {
    // Initialize map
    initMap();

    // Create XML document and headder
    commonCompoundXML.InsertFirstChild(commonCompoundXML.NewDeclaration("xml version=\"1.0\" encoding=\"UTF-8\""));
    // Create root element
    tinyxml2::XMLElement* commonCompounds = commonCompoundXML.NewElement("commonCompounds");    
    
    // Iterate through map and save each compound
    auto it = commonCompMap.begin();
    for (int n = 0; n < commonCompMap.size(); n++, it++)
    {
        compound* comp = it->second;
        saveCommonCompound(commonCompounds, comp);
    }
    
    // Insert common compounds into XML document and saves to file
    commonCompoundXML.InsertEndChild(commonCompounds);
    saveCommonCompoundXML("commonCompounds.xml");
}

/*
* Function: mapInitilization
* Arguments: const char* path
* Warnings: none
* Descriptiom: Initializes the common compound map from the common compound XML file from specified path
* Returns: none
*/
void mapInitilization(const char* path) {
    // Load XML file from path
    commonCompoundXML.LoadFile(path);

    // Tries to access XML file
    try
    {
        // Grabs initial value from the XML file
        tinyxml2::XMLElement* xmlCompound = commonCompoundXML.FirstChildElement("commonCompounds")->FirstChildElement("compound");

        const char* compName;
        const char* compFormula;
        double compMolecularWeight;
        // Iterate through XML file and save each compound
        while (xmlCompound)
        {
            // Grab compound values from XML file
            compName = xmlCompound->FirstChildElement("name")->GetText();
            compFormula = xmlCompound->FirstChildElement("formula")->GetText();
            compMolecularWeight = std::stod(xmlCompound->FirstChildElement("molecular_weight")->GetText());
            
            // Insert compound into common compound map
            commonCompMap[compName] = new compound(compName, compFormula, compMolecularWeight);
            
            // Iterate to next compound
            xmlCompound = xmlCompound->NextSiblingElement("compound");
        }
    }
    // Catch for the XML file not being found
    catch (const std::exception&)
    {
        std::cout << "There was an error reading XML";
    }
}

/*
* Function: getCCP
* Arguments: none
* Warnings: none
* Descriptiom: Returns the common compound XML document
* Returns: tinyxml2::XMLDocument*
*/
tinyxml2::XMLDocument* getCCP()
{
    return &commonCompoundXML;
}

#else
void mapInitilization() {
	compMap["Boc-Leu-OH"] = new compound("Boc-Leu-OH", "C11H21NO4", 231.292);
	compMap["N,O-dimethylhydroxylamine"] = new compound("N,O-dimethylhydroxylamine", "C8H17NO1", 97.54);
    compMap["EDC"] = new compound("EDC", "C8H17N3", 191.7);
    compMap["HOBt"] = new compound("HOBt", "C6H5N3O", 135.12);
    compMap["DIPEA"] = new compound("DIPEA", "C8H19N", 129.24);
    compMap["Boc-Leu-N(O-CH3)CH3"] = new compound("Boc-Leu-N(O-CH3)CH3", "C13H26N2O4", 274.189);
    compMap["TFA-Leu-N(O-CH3)CH3"] = new compound("TFA-Leu-N(O-CH3)CH3", "C10H18F3N2O3", 271.260);
    compMap["CBZ-Leu-Leu-OH"] = new compound("CBZ-Leu-Leu-OH", "C20H30N2O5", 378.469);
    compMap["CBZ-Leu-Leu-N(O-CH3)CH3"] = new compound("CBZ-Leu-Leu-N(O-CH3)CH3", "C26H46N4O6", 534.698);
}
#endif // LOADXML

/*
* Function: compLookup
* Arguments: const char* input
* Warnings: none
* Descriptiom: Returns the compound from the common compound map
* Returns: compound*
*/
compound* compLookup(const char* input) {
    return commonCompMap[input];
}