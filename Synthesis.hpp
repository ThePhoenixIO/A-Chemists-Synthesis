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
    // Maps
    std::unordered_map<const char*, compound*> compMap;
    std::unordered_map<int, reaction*> reactMap;

    int maxID = 0;

    struct longestPath
    {
        reaction* reactionStep;
        int pathLength;
    };

    static synthesis* loadSynthesis();

    // Starting points
    std::vector<reaction*> startingPoints;
    int numStartingPoints = 0;
    int numSteps = 0;

    // Product
    // how to handel? use reaction or compound?
    reaction* product;

    // constructors
    synthesis();
    
    synthesis(reaction* p);

    // Methods
    void addStartingPoint(reaction* r);

    void setProduct(reaction* r);

    bool validSynthesis();
    
    longestPath findLongestPath();

    void rxnTraversal(reaction* rootRxn, std::function<void()> altFunct = nullptr);

    // Acceptible directions are "forward (f)" and "reverse (r)"
    int calculateSynthesis(const char* direction = "forward");

    int saveSynthesis();

    int saveCompoundMap(tinyxml2::XMLDocument mainDoc);

    int saveReactionMap(tinyxml2::XMLDocument mainDoc);

    void saveNode(tinyxml2::XMLDocument mainDoc, std::vector<bool> visited, reaction* element);

    int saveSynthesisGraph(tinyxml2::XMLDocument mainDoc);
};

synthesis* synthesis::loadSynthesis()
{
    return nullptr;
}

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
    if (validSynthesis() == false) { return {nullptr, -1}; }

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
* Arguments: folder title for the synthesis
* Warnings: None
* Description: Saves the synthesis to the given path
* Returns: 0 if successful
*/
int synthesis::saveSynthesis()
{
    pathReturn path = saveAsDialog(L"Save Synthesis", nullptr, L"Synthesis(*.syn)\000*.syn\000All Files(*.*)\000*.*\000");
    if (path.errorCode != 0) { return 1; }

    tinyxml2::XMLDocument doc;
    doc.InsertFirstChild(doc.NewDeclaration("xml version=\"1.0\" encoding=\"UTF-8\""));
    try
    {
        saveCompoundMap(&doc);
    }
    catch (const std::exception&)
    {
        return 2;
    }
    try
    {
        saveReactionMap(&doc);
    }
    catch (const std::exception&)
    {
        return 3;
    }
    try
    {
        saveSynthesisGraph(&doc);
    }
    catch (const std::exception&)
    {
        return 4;
    }
    
    return 0;
}

int synthesis::saveCompoundMap(tinyxml2::XMLDocument mainDoc)
{
    // Create and insert base node
    tinyxml2::XMLElement* xmlCompoundMap = mainDoc.NewElement("compound_map");

    // initialize iterator [it]
    auto it = compMap.begin();
    tinyxml2::XMLElement* name = nullptr;
    tinyxml2::XMLElement* formula = nullptr;
    tinyxml2::XMLElement* molecularWeight = nullptr;
    for (int n = 0; n < compMap.size(); n++, it++)
    {
        compound* comp = it->second;
        tinyxml2::XMLNode* xmlCompound = mainDoc.NewElement("compound");

        // Create, set, and insert name element
        name = mainDoc.NewElement("name");
        name->SetAttribute("type", "string");
        name->SetText(comp->getName());
        xmlCompound->InsertFirstChild(name);

        // Create, set, and insert formula element
        formula = mainDoc.NewElement("formula");
        formula->SetAttribute("type", "string");
        formula->SetText(comp->getFormula());
        xmlCompound->InsertEndChild(formula);

        // Create, set, and insert molecular weight element
        molecularWeight = mainDoc.NewElement("molecular_weight");
        molecularWeight->SetAttribute("type", "double");
        molecularWeight->SetText(comp->getMW());
        xmlCompound->InsertEndChild(molecularWeight);

        xmlCompoundMap->InsertEndChild(xmlCompound);
    }

    // Insert base node into document
    mainDoc.InsertEndChild(xmlCompoundMap);

    return 0;
}

int synthesis::saveReactionMap(tinyxml2::XMLDocument mainDoc)
{
	// Create and insert base node
	tinyxml2::XMLElement* xmlReactionMap = mainDoc.NewElement("reaction_map");

	// initialize iterator [it]
	auto it = reactMap.begin();
	for (int n = 0; n < reactMap.size(); n++, it++)
	{
        reaction* rxn = it->second;
		tinyxml2::XMLNode* xmlReaction = mainDoc.NewElement("reaction");

        // Write ID
        tinyxml2::XMLElement* ID = mainDoc.NewElement("ID");
        ID->SetAttribute("type", "int");
        ID->SetText(rxn->getRID());
        xmlReaction->InsertFirstChild(ID);


        // Write SM and Prod
        tinyxml2::XMLElement* SM = mainDoc.NewElement("starting_material");
        
        tinyxml2::XMLElement* SM_name = mainDoc.NewElement("name");
        SM_name->SetAttribute("type", "string");
        SM_name->SetText(rxn->reactionStartingMaterial->getCompName());
        SM->InsertFirstChild(SM_name);

        tinyxml2::XMLElement* SM_mv = mainDoc.NewElement("mass/volume");
        SM_mv->SetAttribute("type", "double");
        SM_mv->SetText(rxn->reactionStartingMaterial->getMV());
        SM->InsertEndChild(SM_mv);

        tinyxml2::XMLElement* SM_mvu = mainDoc.NewElement("mass/volume_unit");
        SM_mvu->SetAttribute("type", "const char*");
        SM_mvu->SetText(rxn->reactionStartingMaterial->getMVU());
        SM->InsertEndChild(SM_mvu);

        tinyxml2::XMLElement* SM_eq = mainDoc.NewElement("equivalents");
        SM_eq->SetAttribute("type", "float");
        SM_eq->SetText(rxn->reactionStartingMaterial->getEquivalents());
        SM->InsertEndChild(SM_eq);

        xmlReaction->InsertFirstChild(SM);

        tinyxml2::XMLElement* Prod = mainDoc.NewElement("product");
        
        tinyxml2::XMLElement* Prod_name = mainDoc.NewElement("name");
        Prod_name->SetAttribute("type", "string");
        Prod_name->SetText(rxn->reactionProduct->getCompName());

        tinyxml2::XMLElement* Prod_mv = mainDoc.NewElement("mass/volume");
        Prod_mv->SetAttribute("type", "double");
        Prod_mv->SetText(rxn->reactionProduct->getMV());
        Prod->InsertEndChild(Prod_mv);

        tinyxml2::XMLElement* Prod_mvu = mainDoc.NewElement("mass/volume_unit");
        Prod_mvu->SetAttribute("type", "const char*");
        Prod_mvu->SetText(rxn->reactionProduct->getMVU());
        Prod->InsertEndChild(Prod_mvu);

        tinyxml2::XMLElement* Prod_eq = mainDoc.NewElement("equivalents");
        Prod_eq->SetAttribute("type", "float");
        Prod_eq->SetText(rxn->reactionProduct->getEquivalents());
        Prod->InsertEndChild(Prod_eq);

        xmlReaction->InsertEndChild(Prod);

        for (int i = 0; i < rxn->numberOfReagents; i++)
        {
            tinyxml2::XMLElement* reagent = mainDoc.NewElement("reagent");

            tinyxml2::XMLElement* reagent_name = mainDoc.NewElement("name");
            reagent_name->SetAttribute("type", "string");
            reagent_name->SetText(rxn->reactionReagents[i]->getCompName());
            reagent->InsertFirstChild(reagent_name);

            tinyxml2::XMLElement* reagent_mv = mainDoc.NewElement("mass/volume");
            reagent_mv->SetAttribute("type", "double");
            reagent_mv->SetText(rxn->reactionReagents[i]->getMV());
            reagent->InsertEndChild(reagent_mv);

            tinyxml2::XMLElement* reagent_mvu = mainDoc.NewElement("mass/volume_unit");
            reagent_mvu->SetAttribute("type", "const char*");
            reagent_mvu->SetText(rxn->reactionReagents[i]->getMVU());
            reagent->InsertEndChild(reagent_mvu);

            tinyxml2::XMLElement* reagent_eq = mainDoc.NewElement("equivalents");
            reagent_eq->SetAttribute("type", "float");
            reagent_eq->SetText(rxn->reactionReagents[i]->getEquivalents());
            reagent->InsertEndChild(reagent_eq);

            xmlReaction->InsertEndChild(reagent);
        }

		xmlReactionMap->InsertEndChild(xmlReaction);
	}

	// Insert base node into document
	mainDoc.InsertEndChild(xmlReactionMap);

	return 0;
}

void synthesis::saveNode(tinyxml2::XMLDocument mainDoc, std::vector<bool> visited, reaction* element)
{
    int id = element->getRID();
    if (visited[id] == true)
    {
        return;
    }
    else
    {
        tinyxml2::XMLElement* edge = mainDoc.NewElement("edge");
        edge->SetAttribute("sources", id);
        if (element->nextReaction = nullptr)
        {
            edge->SetAttribute("target", -1);
        }
        else
        {
            edge->SetAttribute("target", element->nextReaction->getRID());
        }
        visited[id] = true;
        saveNode(&mainDoc, visited, element->nextReaction);
        return;
    }
}

int synthesis::saveSynthesisGraph(tinyxml2::XMLDocument mainDoc)
{
    // Create and insert base node
    tinyxml2::XMLElement* xmlSynthesisGraph = mainDoc.NewElement("synthesis_graph");

    // Create array vector for node visited
    std::vector<bool> visitNode;
    visitNode.assign(maxID, false);
    int id = 0;

    while (id < maxID)
    {
        saveNode(&mainDoc, visitNode, reactMap[id]);
    }

    // Insert base node into document
    mainDoc.InsertEndChild(xmlSynthesisGraph);

    return 0;
}
#endif // !SYNTHESIS