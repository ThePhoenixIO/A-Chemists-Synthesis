#include"reaction.hpp"
#include<string>

#define COMPLOAD false
#if COMPLOAD
compound* bocLeu = new compound("Boc-Leu-OH", "C11H21NO4", 231.292);
compound* NODHA = new compound("N,O-dimethylhydroxylamine", "C8H17NO1", 97.54);
compound* EDC = new compound("EDC", "C8H17N3", 191.7);
compound* HOBt = new compound("HOBt", "C6H5N3O", 135.12);
compound* DIPEA = new compound("DIPEA", "C8H19N", 129.24);
compound* bocLeuWA = new compound("Boc-Leu-N(O-CH3)CH3", "C13H26N2O4", 274.189);
compound* TFALeuWA = new compound("TFA-Leu-N(O-CH3)CH3", "C10H18F3N2O3", 271.260);
compound* ZLLOH = new compound("CBZ-Leu-Leu-OH", "C20H30N2O5", 378.469);
compound* ZLLLWA = new compound("CBZ-Leu-Leu-N(O-CH3)CH3", "C26H46N4O6", 534.698);
#else
compound* compoundLookup(const char* input)
{
	return compMap[input];
}
#endif

#define TEST true
#if TEST
int main()
{
	mapInitilization();
	
	startingOrProduct sm(compoundLookup("Boc-Leu-OH"), 10, "g");
	reagent WA(compoundLookup("N,O-dimethylhydroxylamine"), &sm, 1, "g");

	reagent rEDC(compoundLookup("EDC"), &sm, 1.2, "g");
	reagent rHOBt(compoundLookup("HOBt"), &sm, 1.1, "g");
	reagent rDIPEA(compoundLookup("DIPEA"), &sm, 2, "g");

	startingOrProduct r1_1(compoundLookup("Boc-Leu-N(O-CH3)CH3"));
	r1_1.calculateProcuct(sm.getMol(), sm.getMVU());

	reaction firstTest(&sm, &r1_1);
	firstTest.addReagent(&WA);
	firstTest.addReagent(&rEDC);
	firstTest.addReagent(&rHOBt);
	firstTest.addReagent(&rDIPEA);

	firstTest.displayReaction();

	double temp = firstTest.reactionProudct->getMol() * compoundLookup("TFA-Leu-N(O-CH3)CH3")->getMW();

	startingOrProduct r1_2(compoundLookup("CBZ-Leu-Leu-OH"), temp, "g");
	startingOrProduct r2_2(compoundLookup("TFA-Leu-N(O-CH3)CH3"), 3.1, "g");
	startingOrProduct r3_1(compoundLookup("CBZ-Leu-Leu-N(O-CH3)CH3"));

	reaction secondTest(&r3_1);
	secondTest.addPotential(&r1_2);
	secondTest.addPotential(&r2_2);
	secondTest.stoeichometry();
	secondTest.addReagent(&rEDC);
	secondTest.addReagent(&rHOBt);
	secondTest.addReagent(&rDIPEA);

	secondTest.displayReaction();
	return 0;
}
#else
int main()
{
	return 0;
}
#endif