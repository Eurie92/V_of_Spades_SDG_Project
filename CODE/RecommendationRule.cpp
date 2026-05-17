#include "RecommendationRule.h"
using namespace std;

/*
 * Function: WeatherMatchRule::score
 * Purpose: Computes weather-match points for a food item.
 * Inputs: A FoodItem object and the user's weather preference.
 * Outputs: Returns 50 points for a matching weather category, otherwise returns 0.
 * Source Basis: This function applies Topic 5 - Decision Control because it uses a conditional expression
 * to choose the score. It also applies Topic 13 - Polymorphism because it overrides the abstract score
 * function from RecommendationRule.
 */
int WeatherMatchRule::score(const FoodItem& food, const UserPreference& preference) const {
    return food.getWeather() == preference.weather ? 50 : 0;
}

/*
 * Function: WeatherMatchRule::explain
 * Purpose: Explains why weather-match points were awarded.
 * Inputs: A FoodItem object and the user's weather preference.
 * Outputs: Returns an explanation string when weather matches, otherwise returns an empty string.
 * Source Basis: This function applies Topic 5 - Decision Control and Topic 13 - Polymorphism because it
 * uses if-statements and overrides the abstract explain function.
 */
string WeatherMatchRule::explain(const FoodItem& food, const UserPreference& preference) const {
    if (food.getWeather() == preference.weather) {
        return "- Weather match: This food is tagged for the user's current weather. (+50)\n";
    }
    return "";
}

/*
 * Function: BudgetMatchRule::score
 * Purpose: Computes budget-match points for a food item.
 * Inputs: A FoodItem object and the user's budget preference.
 * Outputs: Returns 30 points for a matching budget level, otherwise returns 0.
 * Source Basis: This function applies Topic 5 - Decision Control because it uses a conditional expression
 * to choose the score. It also applies Topic 13 - Polymorphism because it overrides the abstract score
 * function from RecommendationRule.
 */
int BudgetMatchRule::score(const FoodItem& food, const UserPreference& preference) const {
    return food.getBudgetLevel() == preference.budgetLevel ? 30 : 0;
}

/*
 * Function: BudgetMatchRule::explain
 * Purpose: Explains why budget-match points were awarded.
 * Inputs: A FoodItem object and the user's budget preference.
 * Outputs: Returns an explanation string when budget level matches, otherwise returns an empty string.
 * Source Basis: This function applies Topic 5 - Decision Control and Topic 13 - Polymorphism because it
 * uses if-statements and overrides the abstract explain function.
 */
string BudgetMatchRule::explain(const FoodItem& food, const UserPreference& preference) const {
    if (food.getBudgetLevel() == preference.budgetLevel) {
        return "- Budget match: This food matches the user's selected budget level. (+30)\n";
    }
    return "";
}

/*
 * Function: AffordabilityRule::score
 * Purpose: Computes affordability points based on whether the food price fits the user's money.
 * Inputs: A FoodItem object and the user's available money.
 * Outputs: Returns 20 points if the food is affordable, otherwise returns 0.
 * Source Basis: This function applies Topic 5 - Decision Control and comparison operators. It also applies
 * Topic 13 - Polymorphism because it overrides the abstract score function from RecommendationRule.
 */
int AffordabilityRule::score(const FoodItem& food, const UserPreference& preference) const {
    return food.getPrice() <= preference.availableMoney ? 20 : 0;
}

/*
 * Function: AffordabilityRule::explain
 * Purpose: Explains why affordability points were awarded.
 * Inputs: A FoodItem object and the user's available money.
 * Outputs: Returns an explanation string when the food is affordable, otherwise returns an empty string.
 * Source Basis: This function applies Topic 5 - Decision Control and Topic 13 - Polymorphism because it
 * uses if-statements and overrides the abstract explain function.
 */
string AffordabilityRule::explain(const FoodItem& food, const UserPreference& preference) const {
    if (food.getPrice() <= preference.availableMoney) {
        return "- Affordable: The price is within the user's available money. (+20)\n";
    }
    return "";
}
