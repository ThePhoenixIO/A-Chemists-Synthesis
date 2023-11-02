#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<algorithm>

#include"startingOrProduct.hpp"
#include"Reagent.hpp"
#include"converter.hpp"
#include"tabulate/tabulate.hpp"

#ifndef REACTION
#define REACTION

class reaction
{
private:
    template <typename type>
    
    void generateBuffer(type* input, std::string buffer[]);

    void clearBuffer(std::string buffer[]);

public:
    // Constructors
    reaction(startingOrProduct* p);
    reaction(startingOrProduct* sm, startingOrProduct* p);

    // list pointers
    reaction* next;

    std::vector<reaction*> previousRxns;

    void setNext(reaction* r);

    void addPrevious(reaction* r);

    void removePrevious(reaction* r);
    
    // Reaction Methods
    int addReagent(reagent* r);

    void displayReaction();

    // Stoeichometry Maths
    std::vector<startingOrProduct*> reactionInputs;
    
    int stoeichometry();

    void addPotential(startingOrProduct* sop);

    // Reaction Elements
    startingOrProduct* reactionStartingMaterial;

    startingOrProduct* reactionProudct;

    std::vector<reagent*> reactionReagents;

    int numberOfReagents = 0;
};

reaction::reaction(startingOrProduct* p)
{
    this->reactionStartingMaterial = nullptr;
    this->reactionProudct = p;
    this->next = nullptr;
}

reaction::reaction(startingOrProduct* sm, startingOrProduct* p)
{
    this->reactionStartingMaterial = sm;
    this->reactionProudct = p;
    this->next = nullptr;
}

int reaction::addReagent(reagent* r)
{
    this->reactionReagents.insert(reactionReagents.end(), r);
    return 0;
}

void reaction::clearBuffer(std::string buffer[])
{
    for (int n = 0; n < 6; n++)
    {
        buffer[n] = "NULL";
    }
}

template<typename type>
void reaction::generateBuffer(type* input, std::string buffer[])
{
    clearBuffer(buffer);
    buffer[0] = input->baseCompound->getName();
    buffer[1] = input->baseCompound->getFormula();
    buffer[2] = std::to_string(input->baseCompound->getMW());
    buffer[3] = std::to_string(input->getMV()) + input->getMVU();
    buffer[4] = std::to_string(input->getMMol());
    buffer[5] = std::to_string(input->getEquivalents());
}

void reaction::displayReaction()
{
    tabulate::Table reactionTable;

    // Buffer and table set up
    std::string tableBuffer[6] = {};
    reactionTable.add_row({"Compound", "Formula", "MW", "M/V", "MMoles", "EQ"});
    
    // Staring Material Part of Table
    generateBuffer<startingOrProduct>(this->reactionStartingMaterial, tableBuffer);
    reactionTable.add_row({tableBuffer[0], tableBuffer[1], tableBuffer[2], tableBuffer[3], tableBuffer[4], tableBuffer[5]});

    // Reagent Part of Table
    for (int i = 0; i < this->reactionReagents.size(); i++)
    {
        generateBuffer<reagent>(this->reactionReagents[i], tableBuffer);
        reactionTable.add_row({tableBuffer[0], tableBuffer[1], tableBuffer[2], tableBuffer[3], tableBuffer[4], tableBuffer[5]});
    }

    // Product Part of Table
    generateBuffer<startingOrProduct>(this->reactionProudct, tableBuffer);
    reactionTable.add_row({tableBuffer[0], tableBuffer[1], tableBuffer[2], tableBuffer[3], tableBuffer[4], tableBuffer[5]});

    std::cout << reactionTable << std::endl;
}

void reaction::addPotential(startingOrProduct* sop)
{
    this->reactionInputs.insert(reactionInputs.end(), sop);
}

int reaction::stoeichometry()
{
    int length = reactionInputs.size();

    auto smIndex = std::min_element(reactionInputs.begin(), reactionInputs.end(), [](startingOrProduct* a, startingOrProduct* b) {return a->getMol() < b->getMol(); }) - reactionInputs.begin();
    this->reactionStartingMaterial = reactionInputs[smIndex];
    reactionInputs.erase(reactionInputs.begin() + smIndex);
    length--;

    for (int i = 0; i < length; i++)
    {
        addReagent(convertReagent(reactionInputs[i], reactionStartingMaterial));
    }
    
    reactionProudct->calculateProcuct(reactionStartingMaterial->getMol(), reactionStartingMaterial->getMVU());

    return 0;
}

void reaction::setNext(reaction* r)
{
    this->next = r;
}

void reaction::addPrevious(reaction* r)
{
    this->previousRxns.insert(previousRxns.end(), r);
}

void reaction::removePrevious(reaction* r)
{
    int length = this->previousRxns.size();
    for (int i = 0; i < length; i++)
    {
        if (this->previousRxns[i] == r)
        {
            this->previousRxns.erase(previousRxns.begin() + i);
            break;
        }
    }
}

#endif // !REACTION