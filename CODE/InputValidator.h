#ifndef INPUTVALIDATOR_H
#define INPUTVALIDATOR_H

#include <string>
using namespace std;

/*
 * Class: InputValidator
 * Purpose: Provides reusable validation and text-cleaning functions for safe user input.
 * Inputs: Console input, prompt messages, numeric ranges, and text values.
 * Outputs: Returns validated numbers, validated strings, normalized text, and accepted category values.
 * Source Basis: This class applies Topic 10 - Functions and Modular Program Design because validation is
 * separated into reusable static functions. It also applies Topic 5 - Decision Control, Topic 7 - Boolean
 * Logic, and looping lessons for repeated validation.
 */
class InputValidator {
public:
    static int getIntInRange(const string& prompt, int min, int max);
    static double getPositiveDouble(const string& prompt);
    static double getPositiveDoubleAllowCancel(const string& prompt);
    static bool isCancelCommand(const string& text);
    static string getWeatherInputAllowCancel();
    static string getBudgetInputAllowCancel();
    static string getNonEmptyLine(const string& prompt);
    static string getWeatherInput();
    static string getBudgetInput();
    static string getYesNoInput(const string& prompt);
    static string toLowerCase(string text);
    static string trim(const string& text);
};

#endif
