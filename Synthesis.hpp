#pragma once
#include "Reaction.hpp"

#ifndef SYNTHESIS
#define SYNTHESIS

/*
* synthesis class
* Overarching orginization class for the synthesis of a compound
* Contains a vector of starting points (reactions) and a product (reaction)
* Contains a map of all compounds and reactions in the synthesis
*/
class synthesis
{
public:
    // constructors
    synthesis();
    synthesis(reaction* p);

    // Starting points
    std::vector<reaction*> startingPoints;
    int numStartingPoints = 0;
    int numSteps = 0;

    // Product
    // how to handel? use reaction or compound?
    reaction* product;

    // Methods
    void addStartingPoint(reaction* r);

    void setProduct(reaction* r);

    bool validSynthesis();

    struct longestPath
    {
        reaction* reactionStep;
        int pathLength;
    };
    
    struct longestPath findLongestPath();

    void rxnTraversal(reaction* rootRxn, std::function<void()> altFunct = nullptr);

    // Acceptible directions are "forward (f)" and "reverse (r)"
    int calculateSynthesis(const char* direction = "forward");

    // TODO: Implement windows dialoge prompt for save location
    int saveSynthesis(const char* path);

    // Maps
    std::unordered_map<const char*, compound*> compMap;
    std::unordered_map<int, reaction*> reactMap;
};

/*
* Constructor: synthesis - default
* Arguments: None
* Warnings: Hardcoded values [nullptr]
* Description: Default constructor for synthesis class
* Returns: None
*/
synthesis::synthesis()
{
    startingPoints = std::vector<reaction*>();
    product = nullptr;
}

/* Constructor: synthesis - Product
* Arguments[p = product]: reaction* p
* Warnings: None
* Description: Constructor for synthesis class given product
* Returns: None
*/
synthesis::synthesis(reaction* p)
{
    startingPoints = std::vector<reaction*>();
    product = p;
}

/*
* Method: addStartingPoint
* Arguments[r = reaction]: reaction* r
* Warnings: None
* Description: Adds a starting point to the synthesis
* Returns: None
*/
void synthesis::addStartingPoint(reaction* r)
{
    startingPoints.insert(startingPoints.end(), r);
    numStartingPoints++;
}

/*
* Method: setProduct
* Arguments[r = product]: reaction* r
* Warnings: None
* Description: Sets the product of the synthesis
* Returns: None
*/
void synthesis::setProduct(reaction* r)
{
    product = r;
}

/*
* Method: validSynthesis
* Arguments: None
* Warnings: None
* Description: Checks if the synthesis is valid
* Returns: true if valid
*/
bool synthesis::validSynthesis()
{
    if (numStartingPoints <= 0)
    {
        std::cout << "Error: No starting points" << std::endl;
        return false;
    }
    // Check if there is a product
    if (product == nullptr)
    {
        std::cout << "Error: No product" << std::endl;
        return false;
    }
    
    return true;
}

/*
* Method: rxnTraversal
* Arguments: reaction* rootRxn
* Warnings: 
*   1. This method is recursive
*   2. Assumes complete synthesis 
*   3. Opperates under normal tree traversal rules (i.e. from product reaction to starting point)
*   4. Default Arguments for altFunct [nullptr]
* Description: Traverses the synthesis tree from products to starting points and "runs" the reactions
* Returns: None
*/
//template<std::function<void> altFunct>
void synthesis::rxnTraversal(reaction* rootRxn, std::function<void()> altFunct)
{
    // Gets the number of reactions that contriubute to the current reaction
    int numRxns = rootRxn->previousReactions.size();
    for (int i = 0; i < numRxns; i++)
    {
        rxnTraversal(rootRxn->previousReactions[i]);
    }
    rootRxn->runReactionForward();
    if (altFunct.target<void()>() == nullptr)
    {
        return;
    }
    else
    {
        altFunct();
        return;
    }
}

/*
* Method: findLongestPath
* Arguments: None
* Warnings: None
* Description: Finds the longest path in the synthesis
* Returns: Struct containing the pointer to start of longest path and the length of the path
* Ask Stratton about returing a struct
*/

synthesis::longestPath synthesis::findLongestPath()
{
    // Synthesis valid check if invalid returns 1
    // Return null struct
    if (validSynthesis() == false) { return ; }

    // Initialization of loop variables
    reaction* currentReaction = nullptr;
    int currentPathLength = 0;

    // Initialization of longest path struct
    longestPath path = { startingPoints[0], 0 };

    for (int i = 0; i < numStartingPoints; i++)
    {
        currentReaction = startingPoints[i];
        currentPathLength = 0;
        // WARNING: USES REACTION* INSTEAD OF COMPOUND* FOR PRODUCT
        while (currentReaction != product)
        {
            currentReaction = currentReaction->nextReaction;
            currentPathLength++;
        }

        // Update longest path if current path is longer
        if (currentPathLength > path.pathLength)
        {
            path.reactionStep = currentReaction;
            path.pathLength = currentPathLength;
        }
    }

    //return 0;
    return path;
}

/*
* Method: calculateSynthesis
* Arguments: const char* direction
* Warnings: Default argument [forward]
* Description: Calculates the synthesis of the product in the given direction
* Returns: 0 if successful [1 if invalid synthesis] [2 if invalid direction]
*/
int synthesis::calculateSynthesis(const char* direction)
{
    // Synthesis valid check
    // Check if there are starting points
    if (validSynthesis() == false) { return 1; }

    longestPath LP = findLongestPath();

    // Calculate synthesis
    if(direction == "forward" || direction == "f")
    {
        // Traverses the synthesis tree from products to starting points and "runs" the reactions
        rxnTraversal(product);
        return 0;
    }
    else if(direction == "reverse" || direction == "r")
    {
        // TODO: Implement reverse synthesis
        // Note: Use rxnTraversal but incoperate flag for product calculations
        return 0;
    }
    else
    {
        std::cout << "Error: Invalid direction" << std::endl;
        return 2;
    }
}

/*
* Method: saveSynthesis
* Arguments: const char* path
* Warnings: None
* Description: Saves the synthesis to the given path
* Returns: 0 if successful
*/
int synthesis::saveSynthesis(const char* path)
{
    pathReturn path = {};

}

#endif // !SYNTHESIS