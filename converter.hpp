#pragma once
#include"startingOrProduct.hpp"
#include "Reagent.hpp"

reagent* convertReagent(startingOrProduct* convertee, startingOrProduct* sm) {
	reagent* converted = new reagent(convertee->baseCompound);
	converted->setMol(convertee->getMol());
	converted->setMV(convertee->getMV(), convertee->getMVU());
	converted->setEquivalents(1);

	converted->calculateReagent(sm);

	return converted;
}