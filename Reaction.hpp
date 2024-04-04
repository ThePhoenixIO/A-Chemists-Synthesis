#pragma once
#include"startingOrProduct.hpp"
#include"Reagent.hpp"
#include"utils.hpp"

#ifndef REACTION
#define REACTION

/*
* reaction Class
* Base unit of the reaction tree (synthesis tree/data structure)
* Contains all the information about a specific reaction
* Contains a pointer to the next and previous reaction in the tree
* Accessable through
* 1. Previous reaction
* 2. Next reaction
* 3. Root synthesis node
* 4. reaction Map with reactionID
*/
class reaction
{
private:
    // specialized buffer generation
    template <typename type>
    void generateBuffer(type* input, std::string buffer[]);

    void clearBuffer(std::string buffer[]);

    // reaction ID
    int reactionID;

public:
    // Constructors
    reaction(startingOrProduct* p, int ID = -1);
    reaction(startingOrProduct* sm, startingOrProduct* p, int ID = -1);

    // list pointers
    reaction* nextReaction;

    /*
    * previous reaction list
    * used to keep track of all the reactions that can lead to this reaction
    * e.g. if this reaction is a convergence point in a synthesis
    * should usually contain 1 reaction
    */
    std::vector<reaction*> previousReactions;

    // Tree data structure manipulation methods
    void setNextReaction(reaction* r);

    void addPrevious(reaction* r);

    void removePrevious(reaction* r);
    
    // Reaction Methods
    int addReagent(reagent* r);

    int runReactionForward();

    void displayReaction();

    const char* textDisplay();

    // Stoeichometry Maths
    std::vector<startingOrProduct*> reactionInputs;
    
    int stoeichometry();

    void addPotential(startingOrProduct* sop);

    // Reaction Elements
    startingOrProduct* reactionStartingMaterial;

    startingOrProduct* reactionProduct; 

    std::vector<reagent*> reactionReagents;

    int numberOfReagents = 0;

    void setRID(int ID);

    int  getRID();
};
// Constructors
/*
* Constructor: reaction - product and rID
* Arguments[p = product]: startingOrProduct* p, int ID
* Warnings: Hardcoded values [nullptr, nullptr]
* Description: Creates a reaction with a product and a reaction ID
* returns: None
*/
reaction::reaction(startingOrProduct* p, int ID)
{
    this->reactionStartingMaterial = nullptr;
    this->reactionProduct = p;
    this->nextReaction = nullptr;
    this->reactionID = ID;
}

/*
* Constructor: reaction - starting material, product and rID
* Arguments[sm = starting material, p = product]: startingOrProduct* sm, startingOrProduct* p, int ID
* Warnings: Hardcoded values [nullptr]
* Description: Creates a reaction with a starting material, product and a reaction ID
* returns: None
*/
reaction::reaction(startingOrProduct* sm, startingOrProduct* p, int ID)
{
    this->reactionStartingMaterial = sm;
    this->reactionProduct = p;
    this->nextReaction = nullptr;
    this->reactionID = ID;
}


// specialized buffer generation
/*
* Method: clearBuffer
* Arguments: std::string buffer[]
* Warnings: None
* Description: Clears the buffer
* returns: None
*/
void reaction::clearBuffer(std::string buffer[])
{
    for (int n = 0; n < 6; n++)
    {
        buffer[n] = "NULL";
    }
}

/*
* Method: generateBuffer
* Arguments: type* input, std::string buffer[]
* Warnings: Typed Function
* Description: Generates a buffer for the reaction table
* returns: None
*/
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


// Tree data structure manipulation methods
/*
* Method: setNextReaction
* Arguments[r = reaction]: reaction* r
* Warnings: None
* Description: Sets the next reaction in the tree
* returns: None
*/
void reaction::setNextReaction(reaction* r)
{
    this->nextReaction = r;
}

/*
* Method: addPrevious
* Arguments[r = reaction]: reaction* r
* Warnings: None
* Description: Adds a reaction to the previous reaction list
* returns: None
*/
void reaction::addPrevious(reaction* r)
{
    this->previousReactions.insert(previousReactions.end(), r);
}

/*
* Method: removePrevious
* Arguments[r = reaction]: reaction* r
* Warnings: None
* Description: Removes the specified reaction from the previous reaction list
* returns: None
*/
void reaction::removePrevious(reaction* r)
{
    // gets the length of the previous reaction list
    int length = this->previousReactions.size();
    // iterates through the list
    for (int i = 0; i < length; i++)
    {
        // if the reaction is found, remove it from the list and stops searching
        if (this->previousReactions[i] == r)
        {
            this->previousReactions.erase(previousReactions.begin() + i);
            break;
        }
    }
}


// Reaction Methods
/*
* Method: addReagent
* Arguments[r = reagent]: reagent* r
* Warnings: None
* Description: Adds a reagent to the reaction
* returns: 0 if successful
*/
int reaction::addReagent(reagent* r)
{
    this->reactionReagents.insert(reactionReagents.end(), r);
    return 0;
}

/*
* Method: runReactionForward
* Arguments: None
* Warnings: No checks for complted reactions, will run under assumption all information is present
* Description: Runs the reaction in the forward direction
* returns: 0 if successful [1 if no starting material]
*/
int reaction::runReactionForward()
{
    // checks if reaction has multiple potential starting materials
    if (reactionInputs.size() > 1)
    {
        stoeichometry();
    }

    // checks if reaction has no starting material
    if (reactionStartingMaterial == nullptr) { return 1; }

    // calculates the reagents
    for (int i = 0; i < numberOfReagents; i++)
    {
        reactionReagents[i]->calculateReagent(reactionStartingMaterial);
    }
    
    reactionProduct->calculateProcuct(reactionStartingMaterial->getMol(), reactionStartingMaterial->getMVU());
    return 0;
}

/*
* Method: displayReaction
* Arguments: None
* Warnings: None
* Description: Displays the reaction in a table using tabulate library
* returns: None
*/
void reaction::displayReaction()
{
    // Table object creation
    tabulate::Table reactionTable;

    // Buffer and table set up 6 columns with names
    std::string tableBuffer[6] = {};
    reactionTable.add_row({ "Compound", "Formula", "MW", "M/V", "MMoles", "EQ" });

    // Staring Material Part of Table
    // Generate table buffer for starting material and adds to table
    generateBuffer<startingOrProduct>(this->reactionStartingMaterial, tableBuffer);
    reactionTable.add_row({ tableBuffer[0], tableBuffer[1], tableBuffer[2], tableBuffer[3], tableBuffer[4], tableBuffer[5] });

    // Reagent Part of Table
    for (int i = 0; i < this->reactionReagents.size(); i++)
    {
        // Generate table buffer for reagent and adds to table
        generateBuffer<reagent>(this->reactionReagents[i], tableBuffer);
        reactionTable.add_row({ tableBuffer[0], tableBuffer[1], tableBuffer[2], tableBuffer[3], tableBuffer[4], tableBuffer[5] });
    }

    // Product Part of Table
    // Generate table buffer for product and adds to table
    generateBuffer<startingOrProduct>(this->reactionProduct, tableBuffer);
    reactionTable.add_row({ tableBuffer[0], tableBuffer[1], tableBuffer[2], tableBuffer[3], tableBuffer[4], tableBuffer[5] });

    // Display Table
    std::cout << reactionTable << std::endl;
}

/*
* Method: textDisplay
* Arguments: None
* Warnings: None
* Description: Displays the reaction in text form
* Returns: const char*
*/
const char* reaction::textDisplay()
{
    std::string starting(reactionStartingMaterial->baseCompound->getName());
    std::string product(reactionProduct->baseCompound->getName());
    std::string buffer = starting + " ---> " + product;
    return buffer.c_str();
}

// Stoeichometry Maths
/*
* Method: stoeichometry
* Arguments: None
* Warnings: None
* Description: Calculates the stoeichometry of the reaction from the potential starting materials
* returns: 0 if successful
*/
int reaction::stoeichometry()
{
    // gets the number of potential starting materials
    int length = reactionInputs.size();

    // gets the starting material with the lowest molar value and saves its index
    auto smIndex = std::min_element(reactionInputs.begin(), reactionInputs.end(), [](startingOrProduct* a, startingOrProduct* b) {return a->getMol() < b->getMol(); }) - reactionInputs.begin();
    // sets the starting material to the starting material with the lowest molar value
    this->reactionStartingMaterial = reactionInputs[smIndex];
    // removes the starting material from the potential starting materials and decrements the length
    reactionInputs.erase(reactionInputs.begin() + smIndex);
    length--;

    // adds the rest of the potential starting materials to the reagents
    for (int i = 0; i < length; i++)
    {
        addReagent(convertReagent(reactionInputs[i], reactionStartingMaterial));
    }

    // calculates the product
    reactionProduct->calculateProcuct(reactionStartingMaterial->getMol(), reactionStartingMaterial->getMVU());

    return 0;
}

/*
* Method: addPotential
* Arguments[sop = startingOrProduct]: startingOrProduct* sop
* Warnings: None
* Description: Adds a potential starting material to the reaction
* returns: None
*/
void reaction::addPotential(startingOrProduct* sop)
{
    this->reactionInputs.insert(reactionInputs.end(), sop);
}


// Reaction Elements
/*
* Method: setRID
* Arguments: int ID
* Warnings: None
* Description: Sets the reaction ID
* returns: None
*/
void reaction::setRID(int ID)
{
    this->reactionID = ID;
}

/*
* Method: getRID
* Arguments: None
* Warnings: None
* Description: Gets the reaction ID
* returns: reactionID
*/
int reaction::getRID()
{
    return this->reactionID;
}
#endif // !REACTION