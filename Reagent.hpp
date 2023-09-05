#pragma once
#include "Compound.hpp"

class reagent : protected compound
{
protected:
	double mv;
	double mol;
	double mmol;
	float eq;

	bool isReagent;
	bool isProduct;
	
public:
	reagent();
	reagent(double reagentMV, double reagentMOL, float reagentEQ, const char* flag = "reagent");

	int setMV(double reagentMV);
	int setMOL(double reagentMOL);
	int setEQ(float reagentEQ);

	int setFlag(const char* flag = "reagent");

	int setReagent(double reagentMV, double reagentMOL = -1, float reagentEQ = -1, const char* flag = "reagent");
};

reagent::reagent()
{
	mv = -1;
	mol = -1;
	mmol = mol / 1000;
	eq = -1;
	
	isReagent = false;
	isProduct = false;
}

reagent::reagent(double reagentMV, double reagentMOL, float reagentEQ, const char* flag = "reagent")
{
	mv = reagentMV;
	mol = reagentMOL;
	mmol = mol / 1000;
	eq = reagentEQ;

	setFlag(flag);
}

int reagent::setMV(double reagentMV)
{
	mv = reagentMV;
	
	return 0;
}

int reagent::setMOL(double reagentMOL)
{
	mol = reagentMOL;
	mmol = mol / 1000;
	
	return 0;
}

int reagent::setEQ(float reagentEQ)
{
	eq = reagentEQ;

	return 0;
}

int reagent::setFlag(const char* flag)
{
	if (flag == "reagent")
	{
		isReagent = true;

		return 0;
	}
	if (flag == "product")
	{
		isProduct = true;
		
		return 0;
	}
	else
	{
		return 1;
	}
}

int reagent::setReagent(double reagentMV, double reagentMOL, float reagentEQ, const char* flag = "reagent")
{
	mv = reagentMV;
	mol = reagentMOL;
	mmol = mol / 1000;
	eq = reagentEQ;

	int flagVal = setFlag(flag);

	if (flagVal == 0)
	{
		return 0;
	}
	else
	{
		return flagVal;
	}
}