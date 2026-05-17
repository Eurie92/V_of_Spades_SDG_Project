#ifndef FOODMANAGER_H
#define FOODMANAGER_H

#include <vector>
#include <string>
#include "FoodItem.h"
using namespace std;

/*
 * Class: FoodManager
 * Purpose: Manages the main food database, including loading, saving, viewing, searching, CRUD operations,
 * recommendations, favorites, and summary reports.
 * Inputs: Food records from database.txt, user menu choices, weather input, budget input, and money input.
 * Outputs: Updates the food collection, writes records to file, and displays food-related results.
 * Source Basis: This class applies Topic 11 - STL Vectors for dynamic collections, Topic 12 - Object-Oriented
 * Programming for class-based system management, and Topic 13 - File Handling for database persistence.
 */
class FoodManager {
private:
    vector<FoodItem> foods;
    vector<FoodItem> favorites;
    int findIndexById(int id) const;
    int generateNextId() const;

public:
    bool loadFromFile(const string& filename);
    bool saveToFile(const string& filename) const;
    void viewAllFoods() const;
    void searchFood() const;
    void addFood();
    void updateFood();
    void deleteFood();
    void recommendByWeather(const string& weather) const;
    void recommendByWeatherAndBudget(const string& weather) const;
    void recommendSmartRanking(const string& weather) const;
    void saveFavoriteFood(const string& weather);
    void viewFavorites() const;
    void generateSummaryReport(const string& currentWeather) const;
    const vector<FoodItem>& getFoods() const;
};

#endif
