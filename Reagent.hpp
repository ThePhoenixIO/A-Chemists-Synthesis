#pragma once
#include "Compound.hpp"

class reagent : protected compound
{
protected:
	double mv;
	double mol;
	double mmol;
	float eq;
	
public:
	reagent();

	reagent(double reagentMV, double reagentMMOL, float reagentEQ);

};

reagent::reagent()
{
	mv = -1;
	mol = -1;
	mmol = mol / 1000;
	eq = -1;
}

reagent::reagent(double reagentMV, double reagentMOL, float reagentEQ)
{
	mv = reagentMV;
	mol = reagentMOL;
	mmol = mol / 1000;
	eq = reagentEQ;
}