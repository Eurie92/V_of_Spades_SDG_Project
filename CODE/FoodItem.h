#ifndef FOODITEM_H
#define FOODITEM_H

#include <string>
using namespace std;

/*
 * Class: FoodItem
 * Purpose: Represents one food record in the WEASOLVE system using private data fields and public methods.
 * Inputs: Food ID, name, weather category, budget level, price, restaurant, and health note.
 * Outputs: Provides controlled access to food information through getters, setters, display, and file conversion.
 * Source Basis: This class applies Topic 12 - Object-Oriented Programming, specifically class creation,
 * encapsulation, private attributes, constructors, and public member functions.
 */
class FoodItem {
private:
    int id;
    string name;
    string weather;
    string budgetLevel;
    double price;
    string restaurant;
    string healthNote;

public:
    FoodItem();
    FoodItem(int id, string name, string weather, string budgetLevel,
             double price, string restaurant, string healthNote);

    int getId() const;
    string getName() const;
    string getWeather() const;
    string getBudgetLevel() const;
    double getPrice() const;
    string getRestaurant() const;
    string getHealthNote() const;

    void setId(int id);
    void setName(string name);
    void setWeather(string weather);
    void setBudgetLevel(string budgetLevel);
    void setPrice(double price);
    void setRestaurant(string restaurant);
    void setHealthNote(string healthNote);

    void display() const;
    string toFileString() const;
};

#endif
