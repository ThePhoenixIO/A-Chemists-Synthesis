#pragma once
#include"Compound.hpp"
#include<unordered_map>
#define LOADXML true

std::unordered_map<const char*, compound*> compMap;
tinyxml2::XMLDocument commonCompoundXML;

#if LOADXML
void initMap() {
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

void saveCommonCompound(tinyxml2::XMLElement* root, compound* comp) {
    tinyxml2::XMLNode* xmlCompound = commonCompoundXML.NewElement("compound");
    
    tinyxml2::XMLElement* name = commonCompoundXML.NewElement("name");
    name->SetAttribute("type", "string");
    name->SetText(comp->getName());
    xmlCompound->InsertFirstChild(name);
    
    tinyxml2::XMLElement* formula = commonCompoundXML.NewElement("formula");
    formula->SetAttribute("type", "string");
    formula->SetText(comp->getFormula());
    xmlCompound->InsertEndChild(formula);

    tinyxml2::XMLElement* molecularWeight = commonCompoundXML.NewElement("molecular_weight");
    molecularWeight->SetAttribute("type", "double");
    molecularWeight->SetText(comp->getMW());
    xmlCompound->InsertEndChild(molecularWeight);

    root->InsertEndChild(xmlCompound);
}

void saveCommonCompoundXML(const char* path) {
    commonCompoundXML.SaveFile(path);
}

void generateCommonCompoundFile() {
    initMap();
    commonCompoundXML.InsertFirstChild(commonCompoundXML.NewDeclaration("xml version=\"1.0\" encoding=\"UTF-8\""));
    tinyxml2::XMLElement* commonCompounds = commonCompoundXML.NewElement("commonCompounds");    
    
    auto it = compMap.begin();
    for (int n = 0; n < compMap.size(); n++, it++)
    {
        compound* comp = it->second;
        saveCommonCompound(commonCompounds, comp);
    }
    
    commonCompoundXML.InsertEndChild(commonCompounds);
    saveCommonCompoundXML("commonCompounds.xml");
}

void mapInitilization(const char* path) {
    commonCompoundXML.LoadFile(path);

    try
    {
        tinyxml2::XMLElement* xmlCompound = commonCompoundXML.FirstChildElement("commonCompounds")->FirstChildElement("compound");

        const char* compName;
        const char* compFormula;
        double compMolecularWeight;
        while (xmlCompound)
        {
            compName = xmlCompound->FirstChildElement("name")->GetText();
            compFormula = xmlCompound->FirstChildElement("formula")->GetText();
            compMolecularWeight = std::stod(xmlCompound->FirstChildElement("molecular_weight")->GetText());
            
            compMap[compName] = new compound(compName, compFormula, compMolecularWeight);
            
            xmlCompound = xmlCompound->NextSiblingElement("compound");
        }
    }
    catch (const std::exception&)
    {
        std::cout << "There was an error reading XML";
    }
}

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

compound* compLookup(const char* input) {
    return compMap[input];
}