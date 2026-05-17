#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "FoodManager.h"
#include "InputValidator.h"
using namespace std;

/*
 * Function: fileExists
 * Purpose: Checks whether a database file exists before the program attempts to use it.
 * Inputs: Filename or path to check.
 * Outputs: Returns true if the file can be opened; otherwise returns false.
 * Source Basis: This function applies Topic 13 - File Handling because it uses ifstream to check an external
 * file. It also applies Topic 10 - Functions and Modular Program Design because file checking is separated
 * into a reusable helper function.
 */
bool fileExists(const string& filename) {
    ifstream file(filename);
    return file.good();
}

/*
 * Function: displayHeader
 * Purpose: Displays the WEASOLVE title banner and system identity.
 * Inputs: None.
 * Outputs: Prints the program header to the console.
 * Source Basis: This function applies Topic 10 - Functions and Modular Program Design because it separates
 * the header display task from the main program flow.
 */
void displayHeader() {
    cout << "\n==========================================\n";
    cout << " WEASOLVE \n";
    cout << " Weather-Based Food Recommendation System\n";
    cout << " SDG 3 - Good Health and Well-Being \n";
    cout << " Final Candidate Version \n";
    cout << "==========================================\n";
}

/*
 * Function: displayMainMenu
 * Purpose: Displays the main menu options available to the user.
 * Inputs: Current weather string.
 * Outputs: Prints the current weather status and menu options to the console.
 * Source Basis: This function applies Topic 10 - Functions and Modular Program Design because it separates
 * menu display from input processing. The conditional expression for weather display applies Topic 5 -
 * Decision Control.
 */
void displayMainMenu(const string& currentWeather) {
    cout << "Current Weather: " << (currentWeather.empty() ? "NOT SET" : currentWeather) << "\n\n";
    cout << "[1] Enter Current Weather\n";
    cout << "[2] View Simple Weather Recommendations\n";
    cout << "[3] Save Favorite Food\n";
    cout << "[4] View Favorite Foods\n";
    cout << "[5] Smart Ranked Recommendation Engine\n";
    cout << "[6] View All Food Records\n";
    cout << "[7] Search Food Record\n";
    cout << "[8] Admin Panel\n";
    cout << "[9] Generate Summary Report\n";
    cout << "[10] Save and Exit\n";
}

/*
 * Function: displayAdminMenu
 * Purpose: Displays the admin panel options for record management.
 * Inputs: None.
 * Outputs: Prints admin CRUD menu options to the console.
 * Source Basis: This function applies Topic 10 - Functions and Modular Program Design because it separates
 * admin menu display from admin menu processing.
 */
void displayAdminMenu() {
    cout << "\n========== ADMIN PANEL ==========\n";
    cout << "[1] Add New Food Record\n";
    cout << "[2] Update Food Record\n";
    cout << "[3] Delete Food Record\n";
    cout << "[4] Return to Main Menu\n";
}

/*
 * Function: verifyAdminAccess
 * Purpose: Restricts access to the admin panel using a simple PIN check.
 * Inputs: Admin PIN entered by the user.
 * Outputs: Returns true when the PIN is correct; otherwise returns false.
 * Source Basis: This function applies Topic 5 - Decision Control because it uses an if-else validation
 * decision. It also applies Topic 10 because admin authentication is separated into a reusable function.
 */
bool verifyAdminAccess() {
    const string ADMIN_PIN = "1234";
    const int MAX_ATTEMPTS = 3;

    for (int attempt = 1; attempt <= MAX_ATTEMPTS; attempt++) {
        string enteredPin = InputValidator::getNonEmptyLine("Enter admin PIN or 0 to go back: ");

        if (InputValidator::isCancelCommand(enteredPin)) {
            cout << "Admin login cancelled. Returning to main menu.\n";
            return false;
        }

        if (enteredPin == ADMIN_PIN) {
            cout << "Admin access granted.\n";
            return true;
        }

        cout << "Incorrect PIN. Attempt " << attempt << " of " << MAX_ATTEMPTS << ".\n";
    }

    cout << "Maximum PIN attempts reached. Returning to main menu.\n";
    return false;
}

/*
 * Function: runAdminPanel
 * Purpose: Runs the admin menu loop for adding, updating, and deleting food records.
 * Inputs: A FoodManager object passed by reference.
 * Outputs: Calls FoodManager CRUD functions based on validated admin choices.
 * Source Basis: This function applies Topic 7 - Looping Structures because it uses a do-while loop,
 * Topic 5 - Decision Control because it uses switch-case branching, Topic 10 - Pass-by-Reference, and
 * Topic 12 - Object Interaction because it calls methods from a FoodManager object.
 */
void runAdminPanel(FoodManager& manager) {
    if (!verifyAdminAccess()) {
        return;
    }

    int adminChoice;
    do {
        displayAdminMenu();
        adminChoice = InputValidator::getIntInRange("Enter admin choice: ", 1, 4);

        switch (adminChoice) {
            case 1:
                manager.addFood();
                break;
            case 2:
                manager.updateFood();
                break;
            case 3:
                manager.deleteFood();
                break;
            case 4:
                cout << "Returning to main menu.\n";
                break;
        }
    } while (adminChoice != 4);
}

/*
 * Function: chooseDatabasePath
 * Purpose: Finds a usable database.txt path from several possible project folder locations.
 * Inputs: None.
 * Outputs: Returns the first existing database path, or database.txt as the default fallback.
 * Source Basis: This function applies Topic 11 - STL Vectors because it stores possible paths in a vector,
 * Topic 7 - Looping Structures because it scans the path list, and Topic 13 - File Handling because it
 * checks external file availability. The use of vector push_back is supported by W3Schools C++ references.
 */
string chooseDatabasePath() {
    vector<string> possiblePaths;
    possiblePaths.push_back("database.txt");
    possiblePaths.push_back("INPUT_DATA/database.txt");
    possiblePaths.push_back("../INPUT_DATA/database.txt");
    possiblePaths.push_back("../../INPUT_DATA/database.txt");

    for (const string& path : possiblePaths) {
        if (fileExists(path)) {
            return path;
        }
    }

    return "database.txt";
}

/*
 * Function: main
 * Purpose: Serves as the main controller of the WEASOLVE console application.
 * Inputs: User menu choices, weather input, recommendation preferences, and admin commands.
 * Outputs: Runs the complete program flow, loads and saves database records, and displays system results.
 * Source Basis: This function applies Topic 5 - Decision Control through switch-case and if-statements,
 * Topic 7 - Looping Structures through the menu loop, Topic 10 - Modular Program Design through function
 * calls, Topic 12 - Object Interaction through the FoodManager object, and Topic 13 - File Handling through
 * database loading and saving.
 */
int main() {
    FoodManager manager;
    string currentWeather = "";
    int choice;
    string databasePath = chooseDatabasePath();

    if (!manager.loadFromFile(databasePath)) {
        cout << "Warning: Program started without loaded database records.\n";
    }

    do {
        displayHeader();
        displayMainMenu(currentWeather);
        choice = InputValidator::getIntInRange("Enter choice: ", 1, 10);

        switch (choice) {
            case 1: {
                string newWeather = InputValidator::getWeatherInputAllowCancel();
                if (newWeather == "0") {
                    cout << "Weather update cancelled. Returning to main menu.\n";
                } else {
                    currentWeather = newWeather;
                    cout << "Current weather set to: " << currentWeather << "\n";
                }
                break;
            }
            case 2:
                if (currentWeather.empty()) {
                    cout << "Please enter current weather first.\n";
                } else {
                    manager.recommendByWeather(currentWeather);
                }
                break;
            case 3:
                if (currentWeather.empty()) {
                    cout << "Please enter current weather first.\n";
                } else {
                    manager.saveFavoriteFood(currentWeather);
                }
                break;
            case 4:
                manager.viewFavorites();
                break;
            case 5:
                if (currentWeather.empty()) {
                    cout << "Please enter current weather first.\n";
                } else {
                    manager.recommendSmartRanking(currentWeather);
                }
                break;
            case 6:
                manager.viewAllFoods();
                break;
            case 7:
                manager.searchFood();
                break;
            case 8:
                runAdminPanel(manager);
                break;
            case 9:
                manager.generateSummaryReport(currentWeather);
                break;
            case 10:
                if (manager.saveToFile(databasePath)) {
                    cout << "Data saved successfully.\n";
                }
                cout << "Thank you for using WEASOLVE!\n";
                break;
        }
    } while (choice != 10);

    return 0;
}
