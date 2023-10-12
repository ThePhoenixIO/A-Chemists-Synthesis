#pragma once
#include"startingOrProduct.hpp"
#include "Reagent.hpp"

reagent* convertReagent(startingOrProduct* convertee) {
	reagent* converted = new reagent(convertee->baseCompound);
	converted->setMol(convertee->getMol());
	converted->setMV(convertee->getMV(), convertee->getMVU());
	converted->setEquivalents(1);

	return converted;
}