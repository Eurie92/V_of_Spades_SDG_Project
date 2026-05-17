#ifndef RECOMMENDATIONRULE_H
#define RECOMMENDATIONRULE_H

#include "FoodItem.h"
#include "UserPreference.h"
#include <string>
using namespace std;

/*
 * Class: RecommendationRule
 * Purpose: Defines the abstract base class for all recommendation scoring rules.
 * Inputs: FoodItem objects and UserPreference data supplied by the recommendation engine.
 * Outputs: Requires derived classes to return scores and explanation messages.
 * Source Basis: This class applies Topic 12 - Object-Oriented Programming and Topic 13 - Polymorphism
 * because it uses virtual functions, inheritance, and abstraction to allow different rule classes to share
 * one common interface.
 */
class RecommendationRule {
public:
    /*
     * Function: ~RecommendationRule
     * Purpose: Provides a virtual destructor for safe cleanup through base class pointers.
     * Inputs: None.
     * Outputs: Allows derived rule objects to be destroyed correctly.
     * Source Basis: This implementation supports Topic 13 - Polymorphism. The use of a virtual destructor
     * is reinforced by W3Schools C++ inheritance and polymorphism references.
     */
    virtual ~RecommendationRule() {}

    /*
     * Function: score
     * Purpose: Defines the required scoring behavior for every recommendation rule.
     * Inputs: A FoodItem object and the user's preference data.
     * Outputs: Returns an integer score contribution.
     * Source Basis: This pure virtual function applies Topic 13 - Polymorphism because derived classes
     * override it to provide different scoring behaviors.
     */
    virtual int score(const FoodItem& food, const UserPreference& preference) const = 0;

    /*
     * Function: explain
     * Purpose: Defines the required explanation behavior for every recommendation rule.
     * Inputs: A FoodItem object and the user's preference data.
     * Outputs: Returns a string explaining why points were given.
     * Source Basis: This pure virtual function applies Topic 13 - Polymorphism because derived classes
     * override it to provide different explanation behaviors.
     */
    virtual string explain(const FoodItem& food, const UserPreference& preference) const = 0;
};

/*
 * Class: WeatherMatchRule
 * Purpose: Gives score points when a food item matches the user's current weather.
 * Inputs: FoodItem weather data and user weather preference.
 * Outputs: Returns weather-based score and explanation.
 * Source Basis: This class applies Topic 13 - Polymorphism because it inherits from RecommendationRule
 * and overrides the score and explain functions.
 */
class WeatherMatchRule : public RecommendationRule {
public:
    int score(const FoodItem& food, const UserPreference& preference) const override;
    string explain(const FoodItem& food, const UserPreference& preference) const override;
};

/*
 * Class: BudgetMatchRule
 * Purpose: Gives score points when a food item matches the user's selected budget level.
 * Inputs: FoodItem budget data and user budget preference.
 * Outputs: Returns budget-based score and explanation.
 * Source Basis: This class applies Topic 13 - Polymorphism because it inherits from RecommendationRule
 * and overrides the score and explain functions.
 */
class BudgetMatchRule : public RecommendationRule {
public:
    int score(const FoodItem& food, const UserPreference& preference) const override;
    string explain(const FoodItem& food, const UserPreference& preference) const override;
};

/*
 * Class: AffordabilityRule
 * Purpose: Gives score points when the food price is within the user's available money.
 * Inputs: FoodItem price data and user's available money.
 * Outputs: Returns affordability-based score and explanation.
 * Source Basis: This class applies Topic 13 - Polymorphism because it inherits from RecommendationRule
 * and overrides the score and explain functions.
 */
class AffordabilityRule : public RecommendationRule {
public:
    int score(const FoodItem& food, const UserPreference& preference) const override;
    string explain(const FoodItem& food, const UserPreference& preference) const override;
};

#endif
