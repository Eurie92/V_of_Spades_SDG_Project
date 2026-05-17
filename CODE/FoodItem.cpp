#include "FoodItem.h"
#include <iostream>
#include <iomanip>
#include <sstream>
using namespace std;

/*
 * Function: FoodItem
 * Purpose: Creates a FoodItem object with safe default values.
 * Inputs: None.
 * Outputs: Initializes the object with empty text fields, zero ID, and zero price.
 * Source Basis: This constructor applies Topic 12 - Object-Oriented Programming because it demonstrates
 * object initialization through a class constructor.
 */
FoodItem::FoodItem() {
    this->id = 0;
    this->name = "";
    this->weather = "";
    this->budgetLevel = "";
    this->price = 0.0;
    this->restaurant = "";
    this->healthNote = "";
}

/*
 * Function: FoodItem
 * Purpose: Creates a complete FoodItem object using provided record details.
 * Inputs: Food ID, name, weather category, budget level, price, restaurant, and health note.
 * Outputs: Initializes the object with complete food information.
 * Source Basis: This constructor applies Topic 12 - Object-Oriented Programming because it demonstrates
 * parameterized object initialization and assignment of values to private class attributes.
 */
FoodItem::FoodItem(int id, string name, string weather, string budgetLevel,
                   double price, string restaurant, string healthNote) {
    this->id = id;
    this->name = name;
    this->weather = weather;
    this->budgetLevel = budgetLevel;
    this->price = price;
    this->restaurant = restaurant;
    this->healthNote = healthNote;
}

/*
 * Function: getId
 * Purpose: Retrieves the food item ID.
 * Inputs: None.
 * Outputs: Returns the integer ID stored inside the object.
 * Source Basis: This function applies Topic 12 - Object-Oriented Programming because it uses a getter
 * method to support encapsulation and controlled access to private data.
 */
int FoodItem::getId() const { return id; }

/*
 * Function: getName
 * Purpose: Retrieves the food item name.
 * Inputs: None.
 * Outputs: Returns the food name stored inside the object.
 * Source Basis: This function applies Topic 12 - Object-Oriented Programming because it uses a getter
 * method to support encapsulation and controlled access to private data.
 */
string FoodItem::getName() const { return name; }

/*
 * Function: getWeather
 * Purpose: Retrieves the weather category assigned to the food item.
 * Inputs: None.
 * Outputs: Returns the weather category string.
 * Source Basis: This function applies Topic 12 - Object-Oriented Programming because it uses a getter
 * method to support encapsulation and controlled access to private data.
 */
string FoodItem::getWeather() const { return weather; }

/*
 * Function: getBudgetLevel
 * Purpose: Retrieves the budget category assigned to the food item.
 * Inputs: None.
 * Outputs: Returns the budget level string.
 * Source Basis: This function applies Topic 12 - Object-Oriented Programming because it uses a getter
 * method to support encapsulation and controlled access to private data.
 */
string FoodItem::getBudgetLevel() const { return budgetLevel; }

/*
 * Function: getPrice
 * Purpose: Retrieves the estimated food price.
 * Inputs: None.
 * Outputs: Returns the price as a double value.
 * Source Basis: This function applies Topic 12 - Object-Oriented Programming because it uses a getter
 * method to support encapsulation and controlled access to private data.
 */
double FoodItem::getPrice() const { return price; }

/*
 * Function: getRestaurant
 * Purpose: Retrieves the restaurant or food source.
 * Inputs: None.
 * Outputs: Returns the restaurant/source string.
 * Source Basis: This function applies Topic 12 - Object-Oriented Programming because it uses a getter
 * method to support encapsulation and controlled access to private data.
 */
string FoodItem::getRestaurant() const { return restaurant; }

/*
 * Function: getHealthNote
 * Purpose: Retrieves the health or wellness note of the food item.
 * Inputs: None.
 * Outputs: Returns the health note string.
 * Source Basis: This function applies Topic 12 - Object-Oriented Programming because it uses a getter
 * method to support encapsulation and controlled access to private data.
 */
string FoodItem::getHealthNote() const { return healthNote; }

/*
 * Function: setId
 * Purpose: Updates the food item ID.
 * Inputs: New integer ID.
 * Outputs: Modifies the private ID attribute.
 * Source Basis: This function applies Topic 12 - Object-Oriented Programming because it uses a setter
 * method to safely modify private data while maintaining encapsulation.
 */
void FoodItem::setId(int id) { this->id = id; }

/*
 * Function: setName
 * Purpose: Updates the food item name.
 * Inputs: New food name as a string.
 * Outputs: Modifies the private name attribute.
 * Source Basis: This function applies Topic 12 - Object-Oriented Programming because it uses a setter
 * method to safely modify private data while maintaining encapsulation.
 */
void FoodItem::setName(string name) { this->name = name; }

/*
 * Function: setWeather
 * Purpose: Updates the weather category of the food item.
 * Inputs: New weather category as a string.
 * Outputs: Modifies the private weather attribute.
 * Source Basis: This function applies Topic 12 - Object-Oriented Programming because it uses a setter
 * method to safely modify private data while maintaining encapsulation.
 */
void FoodItem::setWeather(string weather) { this->weather = weather; }

/*
 * Function: setBudgetLevel
 * Purpose: Updates the budget category of the food item.
 * Inputs: New budget level as a string.
 * Outputs: Modifies the private budgetLevel attribute.
 * Source Basis: This function applies Topic 12 - Object-Oriented Programming because it uses a setter
 * method to safely modify private data while maintaining encapsulation.
 */
void FoodItem::setBudgetLevel(string budgetLevel) { this->budgetLevel = budgetLevel; }

/*
 * Function: setPrice
 * Purpose: Updates the estimated food price.
 * Inputs: New price as a double value.
 * Outputs: Modifies the private price attribute.
 * Source Basis: This function applies Topic 12 - Object-Oriented Programming because it uses a setter
 * method to safely modify private data while maintaining encapsulation.
 */
void FoodItem::setPrice(double price) { this->price = price; }

/*
 * Function: setRestaurant
 * Purpose: Updates the restaurant or food source.
 * Inputs: New restaurant/source text.
 * Outputs: Modifies the private restaurant attribute.
 * Source Basis: This function applies Topic 12 - Object-Oriented Programming because it uses a setter
 * method to safely modify private data while maintaining encapsulation.
 */
void FoodItem::setRestaurant(string restaurant) { this->restaurant = restaurant; }

/*
 * Function: setHealthNote
 * Purpose: Updates the health or wellness note.
 * Inputs: New health note text.
 * Outputs: Modifies the private healthNote attribute.
 * Source Basis: This function applies Topic 12 - Object-Oriented Programming because it uses a setter
 * method to safely modify private data while maintaining encapsulation.
 */
void FoodItem::setHealthNote(string healthNote) { this->healthNote = healthNote; }

/*
 * Function: display
 * Purpose: Displays the food item details in a readable console format.
 * Inputs: Current FoodItem object data.
 * Outputs: Prints the food item information to the console.
 * Source Basis: This function applies Topic 10 - Functions and Modular Program Design because it separates
 * the display task into a reusable function. It also applies Topic 12 because it defines object behavior
 * through a class method.
 */
void FoodItem::display() const {
    cout << "----------------------------------------\n";
    cout << "ID          : " << id << "\n";
    cout << "Food Name   : " << name << "\n";
    cout << "Weather     : " << weather << "\n";
    cout << "Budget      : " << budgetLevel << "\n";
    cout << "Price       : PHP " << fixed << setprecision(2) << price << "\n";
    cout << "Restaurant  : " << restaurant << "\n";
    cout << "Health Note : " << healthNote << "\n";
}

/*
 * Function: toFileString
 * Purpose: Converts a FoodItem object into a pipe-delimited text format for database storage.
 * Inputs: Current FoodItem object data.
 * Outputs: Returns one formatted string that can be written to database.txt.
 * Source Basis: This function applies Topic 10 - Functions and Modular Program Design because it separates
 * formatting logic into a reusable function. It also supports Topic 13 - File Handling because the returned
 * string is used for external text file storage. The use of stringstream and setprecision is supported by
 * W3Schools C++ standard library references.
 */
string FoodItem::toFileString() const {
    stringstream ss;
    ss << id << "|" << name << "|" << weather << "|" << budgetLevel << "|"
       << fixed << setprecision(2) << price << "|" << restaurant << "|" << healthNote;
    return ss.str();
}
