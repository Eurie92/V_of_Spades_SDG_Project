#ifndef RECOMMENDATIONRESULT_H
#define RECOMMENDATIONRESULT_H

#include "FoodItem.h"
#include <string>
using namespace std;

/*
 * Struct: RecommendationResult
 * Purpose: Stores the output of the smart recommendation process.
 * Inputs: A FoodItem object, its computed score, and the explanation of why it was recommended.
 * Outputs: Provides organized recommendation data for ranked display in the console.
 * Source Basis: This struct applies Topic 11 - Structs as Entities because it groups related output data
 * into one structured result used by the recommendation engine.
 */
struct RecommendationResult {
    FoodItem food;
    int score;
    string explanation;
};

#endif
