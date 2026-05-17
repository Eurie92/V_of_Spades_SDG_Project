#ifndef USERPREFERENCE_H
#define USERPREFERENCE_H

#include <string>
using namespace std;

/*
 * Struct: UserPreference
 * Purpose: Groups the user's recommendation preferences into one simple data container.
 * Inputs: Current weather, budget level, and available money.
 * Outputs: Supplies grouped preference data to the recommendation engine and rule classes.
 * Source Basis: This struct applies Topic 11 - Structs as Entities because it groups related user data
 * into one structured variable for cleaner function parameters.
 */
struct UserPreference {
    string weather;
    string budgetLevel;
    double availableMoney;
};

#endif
