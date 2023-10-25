#pragma once
#include"Compound.hpp"
#include<unordered_map>
#define LOADXML false

std::unordered_map<const char*, compound*> compMap;

#if LOADXML

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
