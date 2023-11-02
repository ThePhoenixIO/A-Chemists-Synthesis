#include"reaction.hpp"
#include<string>

#define TEST 1
#if TEST == 0
int main() {
	mapInitilization();
	
	startingOrProduct sm(compLookup("Boc-Leu-OH"), 10, "g");
	reagent WA(compLookup("N,O-dimethylhydroxylamine"), &sm, 1, "g");

	reagent rEDC(compLookup("EDC"), &sm, 1.2, "g");
	reagent rHOBt(compLookup("HOBt"), &sm, 1.1, "g");
	reagent rDIPEA(compLookup("DIPEA"), &sm, 2, "g");

	startingOrProduct r1_1(compLookup("Boc-Leu-N(O-CH3)CH3"));
	r1_1.calculateProcuct(sm.getMol(), sm.getMVU());

	reaction firstTest(&sm, &r1_1);
	firstTest.addReagent(&WA);
	firstTest.addReagent(&rEDC);
	firstTest.addReagent(&rHOBt);
	firstTest.addReagent(&rDIPEA);

	firstTest.displayReaction();

	double temp = firstTest.reactionProudct->getMol() * compLookup("TFA-Leu-N(O-CH3)CH3")->getMW();

	startingOrProduct r1_2(compLookup("CBZ-Leu-Leu-OH"), temp, "g");
	startingOrProduct r2_2(compLookup("TFA-Leu-N(O-CH3)CH3"), 3.1, "g");
	startingOrProduct r3_1(compLookup("CBZ-Leu-Leu-N(O-CH3)CH3"));

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

#elif TEST == 1
int main() {
	mapInitilization("commonCompounds.xml");
	return 0;
}

#else
int main() {
	return 0;
}
#endif
