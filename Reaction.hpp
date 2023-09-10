#pragma once
#include<vector>
#include<string>
#include"StartingMaterial.hpp"
#include"Reagent.hpp"
#include"Product.hpp"
#include"tabulate/tabulate.hpp"

class reaction
{
private:
    template <typename type>
    
    void generateBuffer(type* input, std::string buffer[]);

    void clearBuffer(std::string buffer[]);

protected:
    startingMaterial* reactionStartingMaterial;

    product* reactionProudct;

    std::vector<reagent*> reactionReagents;

    int numberOfReagents = 0;

public:
    reaction(startingMaterial* sm, product* p);

    int addReagent(reagent* r);

    //int addReagents(std::vector<reagent*> reagentVector);

    void displayReaction();
};

reaction::reaction(startingMaterial* sm, product* p)
{
    this->reactionStartingMaterial = sm;

    this->reactionProudct = p;
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
    buffer[0] = input->getName();
    buffer[1] = input->getFormula();
    buffer[2] = std::to_string(input->getMW());
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
    generateBuffer<startingMaterial>(this->reactionStartingMaterial, tableBuffer);
    reactionTable.add_row({tableBuffer[0], tableBuffer[1], tableBuffer[2], tableBuffer[3], tableBuffer[4], tableBuffer[5]});

    // Reagent Part of Table
    for (int i = 0; i < this->reactionReagents.size(); i++)
    {
        generateBuffer<reagent>(this->reactionReagents[i], tableBuffer);
        reactionTable.add_row({tableBuffer[0], tableBuffer[1], tableBuffer[2], tableBuffer[3], tableBuffer[4], tableBuffer[5]});
    }

    // Product Part of Table
    generateBuffer<product>(this->reactionProudct, tableBuffer);
    reactionTable.add_row({tableBuffer[0], tableBuffer[1], tableBuffer[2], tableBuffer[3], tableBuffer[4], tableBuffer[5]});

    std::cout << reactionTable << std::endl;
}
