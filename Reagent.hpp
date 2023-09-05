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
	reagent(double reagentMV, double reagentMOL, float reagentEQ);

	bool setMV(double reagentMV);
	bool setMOL(double reagentMOL);
	bool setEQ(float reagentEQ);

	bool setReagent(double reagentMV, double reagentMOL = -1, float reagentEQ = -1);
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

bool reagent::setMV(double reagentMV)
{
	mv = reagentMV;
	
	return true;
}

bool reagent::setMOL(double reagentMOL)
{
	mol = reagentMOL;
	mmol = mol / 1000;
	
	return true;
}

bool reagent::setEQ(float reagentEQ)
{
	eq = reagentEQ;

	return true;
}

bool reagent::setReagent(double reagentMV, double reagentMOL, float reagentEQ)
{
	mv = reagentMV;
	mol = reagentMOL;
	mmol = mol / 1000;
	eq = reagentEQ;

	return true;
}

