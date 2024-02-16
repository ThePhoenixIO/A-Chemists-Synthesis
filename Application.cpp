#include "synthesis.hpp"
#include <string>

//wchar_t global_path;

#define TEST 3
#if TEST == 0
int main(int argc, char* argv[]) {
	//mapInitilization();
	
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
int main(int argc, char* argv[]) {
	// common compound map initialization and save test
	mapInitilization("commonCompounds.xml");
	return 0;
}

#elif TEST == 2
int displayMenu(std::vector<std::string> menuOptions, std::string prompt, std::string returnOption = "Exit") {
	system("cls");
	int choice = 0;
	std::cout << prompt << std::endl;
	std::cout << "----------------------------------" << std::endl;
	for (int i = 0; i < menuOptions.size(); i++) {
		std::cout << (i + 1) << ". " << menuOptions[i] << std::endl;
	}
	std::cout << menuOptions.size() + 1 << ". " << returnOption << std::endl;
	std::cout << "----------------------------------" << std::endl;
	std::cout << "Only numbers accepte" << std::endl << ">>";
	try
	{
		std::cin >> choice;
	}
	catch(const std::exception& e)
	{
		std::cout << "Invalid input" << std::endl;
		displayMenu(menuOptions, prompt, returnOption);
	}
	return choice;
}

int main(int argc, char* argv[]) {
	std::vector<std::string> mainMenuOptions = { "New Synthesis", "Select Synthesis", "Open Synthesis", "Create Common Compound XML" };
	std::vector<std::string> synthesisMenuOptions = { "Add reaction", "Assign Starting Points", "Assign Product", "Display Synthesis", "Save Synthesis" };
	std::vector<std::string> reactionMenuOptions = { "Add Starting Material", "Add Product", "Add reagent", "Add Potential Starting Material", "Calculate Stoeichometry", "Display Reaction" };

	int choice = -1;
	choice = displayMenu(mainMenuOptions, "Welcome to A Chemists Synthesis!\nThis is the text based version of the program and thus has some limitations to its function.\nPlease select from the options below to continue");
	
	return 0;
}

#elif TEST == 3
int main(int argc, char* argv[]) {
	bool quit = false;
	char* input = new char;
	wchar_t path;
	while (quit != true)
	{
		path = saveAsDialog(L"Test Dioluge Output");
		std::cout << L"returned path: " << path << std::endl;
		std::cout << L"Returned path: " << global_path << std::endl;
		std::cout << "Would you like to quit? (y/n)" << std::endl;
		std::cin >> input;

		if (input == "y") {
			quit = true;
		}
		else {
			quit = false;
		}
	}
	return 1;
}
#else
int main(int argc, char *argv[]) {
	return 0;
}
#endif
