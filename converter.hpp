#pragma once
#include"startingOrProduct.hpp"
#include "Reagent.hpp"

/*
* Function: convertReagent
* Arguments: startingOrProduct* convertee, startingOrProduct* startingMaterial
* Warnings: None
* Description: Converts a startingOrProduct to a reagent
* Returns: reagent*
*/
reagent* convertReagent(startingOrProduct* convertee, startingOrProduct* startingMaterial) {
	reagent* converted = new reagent(convertee->baseCompound);
	converted->setMol(convertee->getMol());
	converted->setMV(convertee->getMV(), convertee->getMVU());
	converted->setEquivalents(1);

	converted->calculateReagent(startingMaterial);

	return converted;
}