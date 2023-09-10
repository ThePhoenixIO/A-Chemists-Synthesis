#include"reaction.hpp"
#include<string>

int test()
{
	startingMaterial sm("Boc-Leu-OH", "C11H21NO4", 231.292, 10);
	reagent WA("N,O-dimethylhydroxylamine", "C8H17NO1", 97.54, &sm, 1);

	reagent EDC("EDC", "C8H17N3", 191.7, &sm, 1.2);
	reagent HOBt("HOBt", "C6H5N3O", 135.12, &sm, 1.1);
	reagent DIPEA("DIPEA", "C8H19N", 129.24, &sm, 2);

	product product1_1("Boc-Leu-NO(CH3)CH3", "C13H26N2O4", 274.189, & sm);

	reaction firstTest(&sm, &product1_1);
	firstTest.addReagent(&WA);
	firstTest.addReagent(&EDC);
	firstTest.addReagent(&HOBt);
	firstTest.addReagent(&DIPEA);

	firstTest.displayReaction();

	return 0;
}

int main()
{
	bool testFlag = true;
	
	if (testFlag == true)
	{
		test();
		return 0;
	}

	return 0;
}