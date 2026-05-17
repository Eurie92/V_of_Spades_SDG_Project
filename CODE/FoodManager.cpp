#include "FoodManager.h"
#include "InputValidator.h"
#include "RecommendationEngine.h"
#include "UserPreference.h"
#include "RecommendationResult.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
using namespace std;

/*
 * Function: isValidWeather
 * Purpose: Checks if a weather value belongs to the accepted WEASOLVE weather categories.
 * Inputs: Weather string to validate.
 * Outputs: Returns true for sunny, rainy, or cold; otherwise returns false.
 * Source Basis: This function applies Topic 5 - Decision Control and Topic 7 - Advanced Boolean Logic
 * because it uses equality comparisons and OR operators to validate categories.
 */
static bool isValidWeather(const string& weather) {
    return weather == "sunny" || weather == "rainy" || weather == "cold";
}

/*
 * Function: isValidBudget
 * Purpose: Checks if a budget value belongs to the accepted WEASOLVE budget categories.
 * Inputs: Budget string to validate.
 * Outputs: Returns true for low, mid, or high; otherwise returns false.
 * Source Basis: This function applies Topic 5 - Decision Control and Topic 7 - Advanced Boolean Logic
 * because it uses equality comparisons and OR operators to validate categories.
 */
static bool isValidBudget(const string& budget) {
    return budget == "low" || budget == "mid" || budget == "high";
}

/*
 * Function: findIndexById
 * Purpose: Searches the food vector for a food item with the given ID.
 * Inputs: Integer food ID.
 * Outputs: Returns the matching vector index or -1 if no record is found.
 * Source Basis: This function applies Topic 7 - Looping Structures and Topic 11 - STL Vectors because it
 * scans a vector using a for loop. The return of -1 also applies Topic 6 - Guard Clauses / sentinel results.
 */
int FoodManager::findIndexById(int id) const {
    for (int i = 0; i < static_cast<int>(foods.size()); i++) {
        if (foods[i].getId() == id) {
            return i;
        }
    }
    return -1;
}

/*
 * Function: generateNextId
 * Purpose: Finds the highest existing food ID and generates the next available ID.
 * Inputs: Current food vector data.
 * Outputs: Returns the next integer ID.
 * Source Basis: This function applies Topic 7 - Looping Structures and Topic 11 - STL Vectors because it
 * scans the vector collection. The comparison condition applies Topic 5 - Decision Control.
 */
int FoodManager::generateNextId() const {
    int highestId = 0;
    for (const FoodItem& food : foods) {
        if (food.getId() > highestId) {
            highestId = food.getId();
        }
    }
    return highestId + 1;
}

/*
 * Function: getFoods
 * Purpose: Provides read-only access to the internal food collection.
 * Inputs: None.
 * Outputs: Returns a constant reference to the vector of FoodItem records.
 * Source Basis: This function applies Topic 12 - Object-Oriented Programming because it supports
 * encapsulation by allowing controlled read-only access to private vector data.
 */
const vector<FoodItem>& FoodManager::getFoods() const {
    return foods;
}

/*
 * Function: loadFromFile
 * Purpose: Loads food records from a pipe-delimited external text database.
 * Inputs: Filename of the database file.
 * Outputs: Returns true if the file is opened and processed; returns false if the file cannot be opened.
 * Source Basis: This function applies Topic 13 - File Handling because it uses ifstream to read external
 * records. It also applies Topic 11 - STL Vectors for storing records, Topic 5 - Decision Control for
 * validation, and Topic 7 - Looping Structures for reading multiple lines. The use of stringstream, getline
 * with delimiters, stoi, stod, and try-catch is based on W3Schools C++ references.
 */
bool FoodManager::loadFromFile(const string& filename) {
    ifstream file(filename.c_str());
    if (!file.is_open()) {
        cout << "Error: Cannot open database file: " << filename << "\n";
        return false;
    }

    foods.clear();
    string line;
    int lineNumber = 0;

    while (getline(file, line)) {
        lineNumber++;
        if (InputValidator::trim(line).empty()) {
            continue;
        }

        stringstream ss(line);
        string idText, name, weather, budgetLevel, priceText, restaurant, healthNote;
        getline(ss, idText, '|');
        getline(ss, name, '|');
        getline(ss, weather, '|');
        getline(ss, budgetLevel, '|');
        getline(ss, priceText, '|');
        getline(ss, restaurant, '|');
        getline(ss, healthNote);

        idText = InputValidator::trim(idText);
        name = InputValidator::trim(name);
        weather = InputValidator::toLowerCase(InputValidator::trim(weather));
        budgetLevel = InputValidator::toLowerCase(InputValidator::trim(budgetLevel));
        priceText = InputValidator::trim(priceText);
        restaurant = InputValidator::trim(restaurant);
        healthNote = InputValidator::trim(healthNote);

        if (idText.empty() || name.empty() || weather.empty() || budgetLevel.empty() ||
            priceText.empty() || restaurant.empty() || healthNote.empty()) {
            cout << "Warning: Skipping incomplete record at line " << lineNumber << ".\n";
            continue;
        }

        if (!isValidWeather(weather) || !isValidBudget(budgetLevel)) {
            cout << "Warning: Skipping invalid category at line " << lineNumber << ".\n";
            continue;
        }

        try {
            int id = stoi(idText);
            double price = stod(priceText);

            if (id <= 0 || price < 0.0) {
                cout << "Warning: Skipping invalid ID/price at line " << lineNumber << ".\n";
                continue;
            }

            if (findIndexById(id) != -1) {
                cout << "Warning: Skipping duplicate ID at line " << lineNumber << ".\n";
                continue;
            }

            foods.push_back(FoodItem(id, name, weather, budgetLevel, price, restaurant, healthNote));
        } catch (...) {
            cout << "Warning: Skipping invalid numeric field at line " << lineNumber << ".\n";
        }
    }

    file.close();
    cout << foods.size() << " food record/s loaded successfully.\n";
    return true;
}

/*
 * Function: saveToFile
 * Purpose: Saves all food records back to the external text database.
 * Inputs: Filename of the database file.
 * Outputs: Returns true if saving succeeds; returns false if the file cannot be opened.
 * Source Basis: This function applies Topic 13 - File Handling because it uses ofstream to write external
 * records. It also applies Topic 11 - STL Vectors because it loops through all food records.
 */
bool FoodManager::saveToFile(const string& filename) const {
    ofstream file(filename.c_str());
    if (!file.is_open()) {
        cout << "Error: Cannot open database file for saving: " << filename << "\n";
        return false;
    }

    for (const FoodItem& food : foods) {
        file << food.toFileString() << "\n";
    }

    file.close();
    return true;
}

/*
 * Function: viewAllFoods
 * Purpose: Displays every food record stored in the system.
 * Inputs: Current food vector data.
 * Outputs: Prints all food records and the total record count.
 * Source Basis: This function applies Topic 7 - Looping Structures and Topic 11 - STL Vectors because it
 * iterates through the food collection. The empty-check applies Topic 6 - Guard Clauses.
 */
void FoodManager::viewAllFoods() const {
    if (foods.empty()) {
        cout << "\nNo food records found.\n";
        return;
    }

    cout << "\n========== ALL FOOD RECORDS ==========\n";
    for (const FoodItem& food : foods) {
        food.display();
    }
    cout << "Total records: " << foods.size() << "\n";
}

/*
 * Function: searchFood
 * Purpose: Searches food records by ID, food name, or restaurant/source.
 * Inputs: User's search option and search value.
 * Outputs: Displays matching food records or an error message if no match is found.
 * Source Basis: This function applies Topic 5 - Decision Control, Topic 7 - Looping Structures, and
 * Topic 11 - STL Vectors. The use of string::find for keyword search is based on W3Schools C++ string
 * handling references.
 */
void FoodManager::searchFood() const {
    if (foods.empty()) {
        cout << "\nNo food records available to search.\n";
        return;
    }

    cout << "\nSearch Food Record\n";
    cout << "[1] Search by ID\n";
    cout << "[2] Search by Name\n";
    cout << "[3] Search by Restaurant\n";
    cout << "[0] Return to Main Menu\n";
    int choice = InputValidator::getIntInRange("Enter choice: ", 0, 3);

    if (choice == 0) {
        cout << "Search cancelled. Returning to main menu.\n";
        return;
    }

    if (choice == 1) {
        int id = InputValidator::getIntInRange("Enter food ID or 0 to go back: ", 0, 1000000);

        if (id == 0) {
            cout << "Search cancelled. Returning to main menu.\n";
            return;
        }

        int index = findIndexById(id);

        if (index == -1) {
            cout << "Food record with ID " << id << " was not found.\n";
        } else {
            foods[index].display();
        }
    } else {
        string keyword = InputValidator::toLowerCase(InputValidator::getNonEmptyLine(choice == 2 ? "Enter food keyword or 0 to go back: " : "Enter restaurant keyword or 0 to go back: "));

        if (InputValidator::isCancelCommand(keyword)) {
            cout << "Search cancelled. Returning to main menu.\n";
            return;
        }

        bool found = false;

        for (const FoodItem& food : foods) {
            string field = choice == 2 ? food.getName() : food.getRestaurant();
            if (InputValidator::toLowerCase(field).find(keyword) != string::npos) {
                food.display();
                found = true;
            }
        }

        if (!found) {
            cout << "No food record matched the keyword.\n";
        }
    }
}

/*
 * Function: addFood
 * Purpose: Adds a new food record through validated admin input.
 * Inputs: Food name, weather, budget, price, restaurant/source, and health note entered by the admin.
 * Outputs: Adds a new FoodItem object to the food vector and displays the generated ID.
 * Source Basis: This function applies Topic 10 - Functions, Topic 11 - STL Vectors, and Topic 12 - Object
 * Interaction because it creates a FoodItem object and stores it in the FoodManager collection.
 */
void FoodManager::addFood() {
    cout << "\n========== ADD NEW FOOD RECORD ==========\n";
    cout << "Type 0 on text/category prompts to cancel and return to the admin menu.\n";
    int newId = generateNextId();

    string name = InputValidator::getNonEmptyLine("Enter food name or 0 to cancel: ");
    if (InputValidator::isCancelCommand(name)) {
        cout << "Add food cancelled.\n";
        return;
    }

    string weather = InputValidator::getWeatherInputAllowCancel();
    if (weather == "0") {
        cout << "Add food cancelled.\n";
        return;
    }

    string budgetLevel = InputValidator::getBudgetInputAllowCancel();
    if (budgetLevel == "0") {
        cout << "Add food cancelled.\n";
        return;
    }

    double price = InputValidator::getPositiveDoubleAllowCancel("Enter estimated price or 0 to cancel: PHP ");
    if (price < 0) {
        cout << "Add food cancelled.\n";
        return;
    }

    string restaurant = InputValidator::getNonEmptyLine("Enter restaurant/source or 0 to cancel: ");
    if (InputValidator::isCancelCommand(restaurant)) {
        cout << "Add food cancelled.\n";
        return;
    }

    string healthNote = InputValidator::getNonEmptyLine("Enter health note or 0 to cancel: ");
    if (InputValidator::isCancelCommand(healthNote)) {
        cout << "Add food cancelled.\n";
        return;
    }

    foods.push_back(FoodItem(newId, name, weather, budgetLevel, price, restaurant, healthNote));
    cout << "Food record added successfully with ID " << newId << ".\n";
}

/*
 * Function: updateFood
 * Purpose: Updates one selected field of an existing food record.
 * Inputs: Food ID, update choice, and the new value for the selected field.
 * Outputs: Modifies the selected FoodItem record in the vector.
 * Source Basis: This function applies Topic 5 - Decision Control because it uses if-statements and switch
 * cases, Topic 6 - Guard Clauses for early returns, and Topic 12 - Encapsulation because it updates private
 * data through setter methods.
 */
void FoodManager::updateFood() {
    if (foods.empty()) {
        cout << "\nNo food records available to update.\n";
        return;
    }

    cout << "\n========== UPDATE FOOD RECORD ==========\n";
    int id = InputValidator::getIntInRange("Enter food ID to update or 0 to cancel: ", 0, 1000000);

    if (id == 0) {
        cout << "Update cancelled.\n";
        return;
    }

    int index = findIndexById(id);

    if (index == -1) {
        cout << "Food record with ID " << id << " was not found.\n";
        return;
    }

    foods[index].display();
    cout << "What do you want to update?\n";
    cout << "[1] Food Name\n[2] Weather\n[3] Budget Level\n[4] Price\n[5] Restaurant\n[6] Health Note\n[7] Cancel\n";
    int choice = InputValidator::getIntInRange("Enter choice: ", 1, 7);

    switch (choice) {
        case 1:
            foods[index].setName(InputValidator::getNonEmptyLine("Enter new food name: "));
            break;
        case 2:
            {
                string weather = InputValidator::getWeatherInputAllowCancel();
                if (weather == "0") {
                    cout << "Update cancelled.\n";
                    return;
                }
                foods[index].setWeather(weather);
            }
            break;
        case 3:
            {
                string budget = InputValidator::getBudgetInputAllowCancel();
                if (budget == "0") {
                    cout << "Update cancelled.\n";
                    return;
                }
                foods[index].setBudgetLevel(budget);
            }
            break;
        case 4:
            {
                double price = InputValidator::getPositiveDoubleAllowCancel("Enter new price or 0 to cancel: PHP ");
                if (price < 0) {
                    cout << "Update cancelled.\n";
                    return;
                }
                foods[index].setPrice(price);
            }
            break;
        case 5:
            foods[index].setRestaurant(InputValidator::getNonEmptyLine("Enter new restaurant/source: "));
            break;
        case 6:
            foods[index].setHealthNote(InputValidator::getNonEmptyLine("Enter new health note: "));
            break;
        case 7:
            cout << "Update cancelled.\n";
            return;
    }

    cout << "Food record updated successfully.\n";
}

/*
 * Function: deleteFood
 * Purpose: Deletes a selected food record after user confirmation.
 * Inputs: Food ID and yes/no confirmation.
 * Outputs: Removes the selected FoodItem from the food vector and removes matching favorites.
 * Source Basis: This function applies Topic 5 - Decision Control, Topic 6 - Guard Clauses, and Topic 11 -
 * STL Vectors because it deletes vector elements. The use of remove_if and a lambda expression is based on
 * W3Schools C++ standard library references.
 */
void FoodManager::deleteFood() {
    if (foods.empty()) {
        cout << "\nNo food records available to delete.\n";
        return;
    }

    cout << "\n========== DELETE FOOD RECORD ==========\n";
    int id = InputValidator::getIntInRange("Enter food ID to delete or 0 to cancel: ", 0, 1000000);

    if (id == 0) {
        cout << "Delete cancelled.\n";
        return;
    }

    int index = findIndexById(id);

    if (index == -1) {
        cout << "Food record with ID " << id << " was not found.\n";
        return;
    }

    foods[index].display();
    string confirm = InputValidator::getYesNoInput("Are you sure you want to delete this record? (yes/no): ");

    if (confirm == "yes") {
        foods.erase(foods.begin() + index);
        favorites.erase(remove_if(favorites.begin(), favorites.end(), [id](const FoodItem& item) {
            return item.getId() == id;
        }), favorites.end());
        cout << "Food record deleted successfully.\n";
    } else {
        cout << "Delete cancelled.\n";
    }
}

/*
 * Function: recommendByWeather
 * Purpose: Displays simple recommendations that match the current weather.
 * Inputs: Current weather string.
 * Outputs: Prints all FoodItem records with a matching weather category.
 * Source Basis: This function applies Topic 5 - Decision Control, Topic 7 - Looping Structures, and
 * Topic 11 - STL Vectors because it filters the food collection using a loop and conditions.
 */
void FoodManager::recommendByWeather(const string& weather) const {
    if (foods.empty()) {
        cout << "\nNo food records available for recommendation.\n";
        return;
    }

    string selectedWeather = InputValidator::toLowerCase(weather);
    bool found = false;
    int count = 0;

    cout << "\n========== SIMPLE WEATHER RECOMMENDATIONS FOR " << selectedWeather << " ==========\n";
    for (const FoodItem& food : foods) {
        if (food.getWeather() == selectedWeather) {
            food.display();
            found = true;
            count++;
        }
    }

    if (!found) {
        cout << "No recommendations found for this weather.\n";
    } else {
        cout << "Total simple recommendation/s found: " << count << "\n";
        cout << "Tip: Use Smart Ranked Recommendation for score + explanation.\n";
    }
}

/*
 * Function: recommendSmartRanking
 * Purpose: Collects user preferences and displays ranked recommendations from the RecommendationEngine.
 * Inputs: Current weather string, user budget level, and available money.
 * Outputs: Prints ranked recommendations with scores and explanations.
 * Source Basis: This function applies Topic 10 - Functions, Topic 11 - STL Vectors, Topic 12 - Object
 * Interaction, and Topic 13 - Polymorphism because it uses RecommendationEngine and RecommendationResult
 * objects to produce ranked recommendations.
 */
void FoodManager::recommendSmartRanking(const string& weather) const {
    if (foods.empty()) {
        cout << "\nNo food records available for smart recommendation.\n";
        return;
    }

    UserPreference preference;
    preference.weather = InputValidator::toLowerCase(weather);
    preference.budgetLevel = InputValidator::getBudgetInputAllowCancel();
    if (preference.budgetLevel == "0") {
        cout << "Smart recommendation cancelled. Returning to main menu.\n";
        return;
    }
    preference.availableMoney = InputValidator::getPositiveDoubleAllowCancel("Enter your available money or 0 to go back: PHP ");
    if (preference.availableMoney < 0) {
        cout << "Smart recommendation cancelled. Returning to main menu.\n";
        return;
    }

    RecommendationEngine engine;
    vector<RecommendationResult> results = engine.recommend(foods, preference);

    cout << "\n========== WEASOLVE SMART RANKED RECOMMENDATIONS ==========\n";
    cout << "Weather: " << preference.weather << "\n";
    cout << "Budget Level: " << preference.budgetLevel << "\n";
    cout << "Available Money: PHP " << fixed << setprecision(2) << preference.availableMoney << "\n";
    cout << "Scoring Formula: Weather 50 + Budget 30 + Affordability 20 = 100\n";

    if (results.empty()) {
        cout << "No strong recommendation found. Try increasing your money or changing budget level.\n";
        return;
    }

    int rank = 1;
    for (const RecommendationResult& result : results) {
        cout << "\nRank #" << rank << " | Score: " << result.score << "/100\n";
        result.food.display();
        cout << "Why recommended:\n" << result.explanation;
        rank++;
    }
}

/*
 * Function: recommendByWeatherAndBudget
 * Purpose: Redirects weather-and-budget recommendation requests to the smart ranking engine.
 * Inputs: Current weather string.
 * Outputs: Displays smart ranked recommendations.
 * Source Basis: This function applies Topic 10 - Functions and Modular Program Design because it reuses
 * the existing smart ranking function instead of duplicating recommendation logic.
 */
void FoodManager::recommendByWeatherAndBudget(const string& weather) const {
    recommendSmartRanking(weather);
}

/*
 * Function: saveFavoriteFood
 * Purpose: Allows the user to save a weather-matching food item into the session favorites list.
 * Inputs: Current weather and selected food ID.
 * Outputs: Adds the selected FoodItem to the favorites vector if valid and not duplicated.
 * Source Basis: This function applies Topic 5 - Decision Control, Topic 6 - Guard Clauses, Topic 7 -
 * Looping Structures, and Topic 11 - STL Vectors because it validates, searches, and stores favorite records.
 */
void FoodManager::saveFavoriteFood(const string& weather) {
    if (foods.empty()) {
        cout << "\nNo food records available to save as favorite.\n";
        return;
    }

    string selectedWeather = InputValidator::toLowerCase(weather);
    bool hasMatch = false;

    cout << "\n========== FOODS AVAILABLE FOR FAVORITES ==========\n";
    for (const FoodItem& food : foods) {
        if (food.getWeather() == selectedWeather) {
            cout << "ID " << food.getId() << " - " << food.getName() << " (PHP " << fixed << setprecision(2) << food.getPrice() << ")\n";
            hasMatch = true;
        }
    }

    if (!hasMatch) {
        cout << "No foods are available for the current weather.\n";
        return;
    }

    while (true) {
        int id = InputValidator::getIntInRange("Enter the ID of the food to save as favorite or 0 to go back: ", 0, 1000000);

        if (id == 0) {
            cout << "Favorite selection cancelled. Returning to main menu.\n";
            return;
        }

        int index = findIndexById(id);

        if (index == -1 || foods[index].getWeather() != selectedWeather) {
            cout << "Invalid ID. Please choose a food listed for the current weather, or enter 0 to go back.\n";
            continue;
        }

        bool alreadyFavorite = false;
        for (const FoodItem& favorite : favorites) {
            if (favorite.getId() == id) {
                alreadyFavorite = true;
                break;
            }
        }

        if (alreadyFavorite) {
            cout << "This food is already in your favorites. Choose another ID or enter 0 to go back.\n";
            continue;
        }

        favorites.push_back(foods[index]);
        cout << foods[index].getName() << " was saved to favorites.\n";
        return;
    }
}

/*
 * Function: viewFavorites
 * Purpose: Displays all food items saved in the session favorites list.
 * Inputs: Current favorites vector data.
 * Outputs: Prints favorite food records and the total favorite count.
 * Source Basis: This function applies Topic 7 - Looping Structures and Topic 11 - STL Vectors because it
 * iterates through the favorites collection. The empty-check applies Topic 6 - Guard Clauses.
 */
void FoodManager::viewFavorites() const {
    if (favorites.empty()) {
        cout << "\nNo favorite foods saved yet.\n";
        return;
    }

    cout << "\n========== FAVORITE FOODS ==========\n";
    for (const FoodItem& food : favorites) {
        food.display();
    }
    cout << "Total favorite/s: " << favorites.size() << "\n";
}

/*
 * Function: generateSummaryReport
 * Purpose: Generates a statistical summary of food records by weather, budget, price, and favorites.
 * Inputs: Current weather string and current food/favorites vector data.
 * Outputs: Prints total records, category counts, average price, cheapest food, and most expensive food.
 * Source Basis: This function applies Topic 7 - Looping Structures, Topic 5 - Decision Control, and
 * Topic 11 - STL Vectors because it counts and analyzes records in a collection. Pointer use for cheapest
 * and most expensive tracking is based on W3Schools C++ reference material.
 */
void FoodManager::generateSummaryReport(const string& currentWeather) const {
    int sunnyCount = 0, rainyCount = 0, coldCount = 0;
    int lowCount = 0, midCount = 0, highCount = 0;
    double totalPrice = 0.0;
    const FoodItem* cheapest = nullptr;
    const FoodItem* mostExpensive = nullptr;

    for (const FoodItem& food : foods) {
        if (food.getWeather() == "sunny") sunnyCount++;
        else if (food.getWeather() == "rainy") rainyCount++;
        else if (food.getWeather() == "cold") coldCount++;

        if (food.getBudgetLevel() == "low") lowCount++;
        else if (food.getBudgetLevel() == "mid") midCount++;
        else if (food.getBudgetLevel() == "high") highCount++;

        totalPrice += food.getPrice();
        if (cheapest == nullptr || food.getPrice() < cheapest->getPrice()) cheapest = &food;
        if (mostExpensive == nullptr || food.getPrice() > mostExpensive->getPrice()) mostExpensive = &food;
    }

    cout << "\n========== WEASOLVE SUMMARY REPORT ==========\n";
    cout << "Current weather : " << (currentWeather.empty() ? "NOT SET" : currentWeather) << "\n";
    cout << "Total food records : " << foods.size() << "\n";
    cout << "Total favorite foods : " << favorites.size() << "\n";
    cout << "\nWeather counts:\nSunny: " << sunnyCount << " | Rainy: " << rainyCount << " | Cold: " << coldCount << "\n";
    cout << "Budget counts:\nLow: " << lowCount << " | Mid: " << midCount << " | High: " << highCount << "\n";

    if (!foods.empty()) {
        cout << "Average food price : PHP " << fixed << setprecision(2) << (totalPrice / foods.size()) << "\n";
    }
    if (cheapest != nullptr) {
        cout << "Cheapest food : " << cheapest->getName() << " (PHP " << fixed << setprecision(2) << cheapest->getPrice() << ")\n";
    }
    if (mostExpensive != nullptr) {
        cout << "Most expensive food : " << mostExpensive->getName() << " (PHP " << fixed << setprecision(2) << mostExpensive->getPrice() << ")\n";
    }
    cout << "============================================\n";
}
