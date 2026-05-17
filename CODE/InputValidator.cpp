#include "InputValidator.h"
#include <iostream>
#include <limits>
#include <algorithm>
#include <cctype>
#include <sstream>
using namespace std;

/*
 * Function: getIntInRange
 * Purpose: Repeatedly asks the user for a whole number until the value is within the accepted range.
 * Inputs: Prompt message, minimum allowed value, and maximum allowed value.
 * Outputs: Returns a validated integer with no extra letters or symbols attached.
 * Source Basis: This function applies Topic 5 - Decision Control and Topic 7 - Looping Structures because
 * it uses if-statements and a while loop for repeated validation. The line-based parsing and stringstream
 * validation are based on W3Schools C++ input stream and string stream references.
 */
int InputValidator::getIntInRange(const string& prompt, int min, int max) {
    string input;
    int value;

    while (true) {
        cout << prompt;
        getline(cin, input);
        input = trim(input);

        stringstream ss(input);
        char extra;

        if (ss >> value && !(ss >> extra) && value >= min && value <= max) {
            return value;
        }

        cout << "Invalid input. Please enter a whole number from " << min << " to " << max << ".\n";
    }
}

/*
 * Function: getPositiveDouble
 * Purpose: Repeatedly asks the user for a positive decimal number.
 * Inputs: Prompt message displayed to the user.
 * Outputs: Returns a validated positive double value with no extra letters or symbols attached.
 * Source Basis: This function applies Topic 5 - Decision Control and Topic 7 - Looping Structures because
 * it uses conditional validation inside a repeated loop. The strict line-based numeric validation uses
 * stringstream, which is based on W3Schools C++ string stream references.
 */
double InputValidator::getPositiveDouble(const string& prompt) {
    string input;
    double value;

    while (true) {
        cout << prompt;
        getline(cin, input);
        input = trim(input);

        stringstream ss(input);
        char extra;

        if (ss >> value && !(ss >> extra) && value > 0) {
            return value;
        }

        cout << "Invalid input. Please enter a positive number only.\n";
    }
}

/*
 * Function: getPositiveDoubleAllowCancel
 * Purpose: Repeatedly asks the user for a positive decimal number while allowing 0 as a cancel command.
 * Inputs: Prompt message displayed to the user.
 * Outputs: Returns a positive double value, or -1 when the user enters 0 to cancel.
 * Source Basis: This function applies Topic 5 - Decision Control, Topic 6 - Guard Clauses, Topic 7 -
 * Looping Structures, and Topic 10 - Modular Program Design because it validates numeric input and adds a
 * reusable back option. The strict stringstream parsing is based on W3Schools C++ references.
 */
double InputValidator::getPositiveDoubleAllowCancel(const string& prompt) {
    string input;
    double value;

    while (true) {
        cout << prompt;
        getline(cin, input);
        input = trim(input);

        if (isCancelCommand(input)) {
            return -1.0;
        }

        stringstream ss(input);
        char extra;

        if (ss >> value && !(ss >> extra) && value > 0) {
            return value;
        }

        cout << "Invalid input. Please enter a positive number only, or 0 to go back.\n";
    }
}

/*
 * Function: getNonEmptyLine
 * Purpose: Repeatedly asks the user for text until a non-empty value is entered.
 * Inputs: Prompt message displayed to the user.
 * Outputs: Returns a trimmed non-empty string.
 * Source Basis: This function applies Topic 5 - Decision Control and Topic 7 - Looping Structures because
 * it validates user input with conditions inside a loop. It also applies Topic 10 because it separates
 * reusable string input validation into its own function.
 */
string InputValidator::getNonEmptyLine(const string& prompt) {
    string text;
    while (true) {
        cout << prompt;
        getline(cin, text);
        text = trim(text);
        if (!text.empty()) {
            return text;
        }
        cout << "Input cannot be empty or whitespace only.\n";
    }
}

/*
 * Function: isCancelCommand
 * Purpose: Checks whether the user entered 0 as a cancel or back command.
 * Inputs: User-entered text.
 * Outputs: Returns true when the trimmed input is exactly 0; otherwise returns false.
 * Source Basis: This function applies Topic 5 - Decision Control and Topic 10 - Functions because it
 * separates repeated cancel-checking logic into one reusable helper function.
 */
bool InputValidator::isCancelCommand(const string& text) {
    return trim(text) == "0";
}

/*
 * Function: getWeatherInput
 * Purpose: Accepts only valid weather categories used by the WEASOLVE recommendation system.
 * Inputs: User-entered weather text from the console.
 * Outputs: Returns a lowercase weather value: sunny, rainy, or cold.
 * Source Basis: This function applies Topic 5 - Decision Control, Topic 7 - Advanced Boolean Logic, and
 * Topic 10 - Functions because it uses repeated validation and reusable category-checking logic.
 */
string InputValidator::getWeatherInput() {
    while (true) {
        string weather = toLowerCase(getNonEmptyLine("Enter current weather (sunny/rainy/cold): "));
        if (weather == "sunny" || weather == "rainy" || weather == "cold") {
            return weather;
        }
        cout << "Invalid weather category. Allowed values: sunny, rainy, cold.\n";
    }
}

/*
 * Function: getWeatherInputAllowCancel
 * Purpose: Accepts valid weather categories or allows the user to return using 0.
 * Inputs: User-entered weather text from the console.
 * Outputs: Returns sunny, rainy, cold, or 0 when the user cancels.
 * Source Basis: This function applies Topic 5 - Decision Control, Topic 6 - Guard Clauses, Topic 7 -
 * Looping Structures, and Topic 10 - Modular Program Design because it provides reusable idiot-proof input.
 */
string InputValidator::getWeatherInputAllowCancel() {
    while (true) {
        string weather = toLowerCase(getNonEmptyLine("Enter current weather (sunny/rainy/cold) or 0 to go back: "));
        if (isCancelCommand(weather)) {
            return "0";
        }
        if (weather == "sunny" || weather == "rainy" || weather == "cold") {
            return weather;
        }
        cout << "Invalid weather category. Allowed values: sunny, rainy, cold, or 0 to go back.\n";
    }
}

/*
 * Function: getBudgetInput
 * Purpose: Accepts only valid budget categories used by the WEASOLVE recommendation system.
 * Inputs: User-entered budget text from the console.
 * Outputs: Returns a lowercase budget value: low, mid, or high.
 * Source Basis: This function applies Topic 5 - Decision Control, Topic 7 - Advanced Boolean Logic, and
 * Topic 10 - Functions because it uses repeated validation and reusable category-checking logic.
 */
string InputValidator::getBudgetInput() {
    while (true) {
        string budget = toLowerCase(getNonEmptyLine("Enter budget level (low/mid/high): "));
        if (budget == "low" || budget == "mid" || budget == "high") {
            return budget;
        }
        cout << "Invalid budget level. Allowed values: low, mid, high.\n";
    }
}

/*
 * Function: getBudgetInputAllowCancel
 * Purpose: Accepts valid budget categories or allows the user to return using 0.
 * Inputs: User-entered budget text from the console.
 * Outputs: Returns low, mid, high, or 0 when the user cancels.
 * Source Basis: This function applies Topic 5 - Decision Control, Topic 6 - Guard Clauses, Topic 7 -
 * Looping Structures, and Topic 10 - Modular Program Design because it provides reusable idiot-proof input.
 */
string InputValidator::getBudgetInputAllowCancel() {
    while (true) {
        string budget = toLowerCase(getNonEmptyLine("Enter budget level (low/mid/high) or 0 to go back: "));
        if (isCancelCommand(budget)) {
            return "0";
        }
        if (budget == "low" || budget == "mid" || budget == "high") {
            return budget;
        }
        cout << "Invalid budget level. Allowed values: low, mid, high, or 0 to go back.\n";
    }
}

/*
 * Function: getYesNoInput
 * Purpose: Accepts only yes or no answers for confirmation prompts.
 * Inputs: Prompt message and user-entered response.
 * Outputs: Returns a lowercase "yes" or "no" string.
 * Source Basis: This function applies Topic 5 - Decision Control, Topic 7 - Advanced Boolean Logic, and
 * Topic 10 - Functions because it uses reusable validation for confirmation decisions.
 */
string InputValidator::getYesNoInput(const string& prompt) {
    while (true) {
        string answer = toLowerCase(getNonEmptyLine(prompt));
        if (answer == "yes" || answer == "no") {
            return answer;
        }
        cout << "Please answer only yes or no.\n";
    }
}

/*
 * Function: toLowerCase
 * Purpose: Converts text into lowercase to make comparisons consistent.
 * Inputs: A string value that may contain uppercase or mixed-case letters.
 * Outputs: Returns the lowercase version of the string.
 * Source Basis: This function supports Topic 10 - Functions and Modular Program Design because it separates
 * reusable text normalization logic. The use of transform, lambda syntax, and tolower is based on W3Schools
 * C++ standard library references.
 */
string InputValidator::toLowerCase(string text) {
    transform(text.begin(), text.end(), text.begin(), [](unsigned char c) {
        return static_cast<char>(tolower(c));
    });
    return text;
}

/*
 * Function: trim
 * Purpose: Removes leading and trailing whitespace from text.
 * Inputs: A string that may contain extra spaces before or after the actual content.
 * Outputs: Returns a cleaned string without leading or trailing whitespace.
 * Source Basis: This function applies Topic 7 - Looping Structures because it scans characters using while
 * loops. The use of size_t, isspace, and substr is based on W3Schools C++ string handling references.
 */
string InputValidator::trim(const string& text) {
    size_t start = 0;
    while (start < text.size() && isspace(static_cast<unsigned char>(text[start]))) {
        start++;
    }

    size_t end = text.size();
    while (end > start && isspace(static_cast<unsigned char>(text[end - 1]))) {
        end--;
    }

    return text.substr(start, end - start);
}
