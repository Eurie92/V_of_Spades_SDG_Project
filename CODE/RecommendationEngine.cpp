#include "RecommendationEngine.h"
#include <algorithm>
using namespace std;

/*
 * Function: RecommendationEngine
 * Purpose: Initializes the smart recommendation engine by adding all scoring rule objects.
 * Inputs: None.
 * Outputs: Creates a rule list containing weather, budget, and affordability rules.
 * Source Basis: This constructor applies Topic 12 - Object-Oriented Programming and Topic 13 - Polymorphism
 * because it stores derived rule objects using base class pointers. The use of unique_ptr is based on
 * W3Schools C++ smart pointer references.
 */
RecommendationEngine::RecommendationEngine() {
    rules.push_back(unique_ptr<RecommendationRule>(new WeatherMatchRule()));
    rules.push_back(unique_ptr<RecommendationRule>(new BudgetMatchRule()));
    rules.push_back(unique_ptr<RecommendationRule>(new AffordabilityRule()));
}

/*
 * Function: recommend
 * Purpose: Evaluates all foods using polymorphic rules, filters strong matches, and sorts ranked results.
 * Inputs: Vector of FoodItem records and the user's preference data.
 * Outputs: Returns affordable RecommendationResult objects with scores of 70 or higher.
 * Source Basis: This function applies Topic 11 - STL Vectors because it stores and processes collections,
 * Topic 7 - Looping Structures because it uses range-based loops, Topic 5 - Decision Control because it
 * filters by affordability and score, and Topic 13 - Polymorphism because it calls overridden rule functions. The use of
 * std::sort and lambda expressions is based on W3Schools C++ standard library references.
 */
vector<RecommendationResult> RecommendationEngine::recommend(const vector<FoodItem>& foods,
                                                             const UserPreference& preference) const {
    vector<RecommendationResult> results;

    for (const FoodItem& food : foods) {
        if (food.getPrice() > preference.availableMoney) {
            continue;
        }

        int totalScore = 0;
        string explanation = "";

        for (const unique_ptr<RecommendationRule>& rule : rules) {
            int ruleScore = rule->score(food, preference);
            totalScore += ruleScore;

            if (ruleScore > 0) {
                explanation += rule->explain(food, preference);
            }
        }

        if (totalScore >= 70) {
            RecommendationResult result;
            result.food = food;
            result.score = totalScore;
            result.explanation = explanation;
            results.push_back(result);
        }
    }

    sort(results.begin(), results.end(), [](const RecommendationResult& a, const RecommendationResult& b) {
        if (a.score != b.score) {
            return a.score > b.score;
        }
        return a.food.getPrice() < b.food.getPrice();
    });

    return results;
}
