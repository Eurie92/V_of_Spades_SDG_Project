#ifndef RECOMMENDATIONENGINE_H
#define RECOMMENDATIONENGINE_H

#include "FoodItem.h"
#include "UserPreference.h"
#include "RecommendationResult.h"
#include "RecommendationRule.h"
#include <vector>
#include <memory>
using namespace std;

/*
 * Class: RecommendationEngine
 * Purpose: Manages the polymorphic recommendation rules and generates ranked food recommendations.
 * Inputs: A vector of FoodItem records and one UserPreference structure.
 * Outputs: Returns a vector of RecommendationResult records sorted by score and affordability.
 * Source Basis: This class applies Topic 11 - STL Vectors, Topic 12 - Object-Oriented Programming, and
 * Topic 13 - Polymorphism because it stores multiple derived rule objects and processes them through a
 * shared RecommendationRule interface. The use of unique_ptr is supported by W3Schools C++ references.
 */
class RecommendationEngine {
private:
    vector<unique_ptr<RecommendationRule>> rules;

public:
    RecommendationEngine();
    vector<RecommendationResult> recommend(const vector<FoodItem>& foods,
                                           const UserPreference& preference) const;
};

#endif
