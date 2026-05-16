# WEASOLVE: Weather-Based Food Recommendation System

## Project Overview

WEASOLVE is a C++ console-based Weather-Based Food Recommendation System developed for CC103 - Computer Programming 2. The system recommends food items based on the user's current weather condition, budget preference, available money, and basic health suitability.

The project supports SDG 3 - Good Health and Well-Being by helping users make practical food choices based on weather, affordability, and wellness-related considerations.

WEASOLVE demonstrates modular C++ programming, object-oriented programming, file handling, input validation, CRUD operations, and a polymorphic rule-based recommendation engine.

## Course Information

**Course:** CC103 - Computer Programming 2  
**Instructor:** Miss Justin Louise R. Neypes  
**Project Type:** Final Project / Final Examination  
**Group:** Group V of Spades  
**Project Name:** WEASOLVE  

## Target Sustainable Development Goal

**SDG 3 - Good Health and Well-Being**

WEASOLVE supports SDG 3 by recommending food choices that consider weather conditions, affordability, and basic health suitability. The system encourages users to choose meals that are appropriate for their environment, budget, and wellness needs.

## Problem Statement

Students and everyday consumers often choose food based only on cravings, availability, or price. However, weather conditions, budget limitations, and health considerations can affect whether a food choice is practical or suitable.

WEASOLVE addresses this problem by providing a structured recommendation system that evaluates food items using multiple criteria. Instead of simply listing available food, the system ranks recommendations based on weather match, budget match, affordability, and health suitability.

## Project Objectives

The objectives of WEASOLVE are:

1. To create a C++ console application that recommends food based on weather and user preferences.
2. To demonstrate object-oriented programming concepts such as encapsulation, abstraction, inheritance, and polymorphism.
3. To apply modular programming through multiple header and implementation files.
4. To use file handling for loading and saving food records through an external text database.
5. To provide CRUD functionality through an admin panel.
6. To prevent common input errors through a dedicated input validation system.
7. To produce a project that is suitable for academic evaluation, documentation, and portfolio presentation.

## Key Features

- Weather-based food recommendation
- Budget-based filtering and scoring
- Affordability checking based on user money
- Health suitability scoring
- Ranked recommendation results
- Admin panel with PIN verification
- Add, view, search, update, and delete food records
- External text file database using pipe-delimited records
- Input validation for numbers, text, weather, and budget categories
- Summary report generation
- Favorites feature for selected recommendations
- Modular multi-file C++ architecture

## System Architecture

WEASOLVE uses a modular architecture where each file has a specific responsibility.

| File | Responsibility |
|---|---|
| `main.cpp` | Main controller, menu system, user interaction, admin panel, and system integration |
| `FoodItem.h` / `FoodItem.cpp` | Defines the encapsulated food entity used by the system |
| `FoodManager.h` / `FoodManager.cpp` | Manages food records, CRUD operations, searching, reporting, and file handling |
| `InputValidator.h` / `InputValidator.cpp` | Handles safe user input and prevents invalid input crashes |
| `UserPreference.h` | Stores grouped user preference data |
| `RecommendationResult.h` | Stores food recommendation output with score and explanation |
| `RecommendationRule.h` / `RecommendationRule.cpp` | Defines the abstract rule class and derived polymorphic scoring rules |
| `RecommendationEngine.h` / `RecommendationEngine.cpp` | Applies recommendation rules, computes total scores, and ranks results |
| `database.txt` | External food record database |

## Object-Oriented Programming Concepts Used

### Encapsulation

The `FoodItem` class stores food information in private data members and provides public getters and setters. This protects the internal data from direct modification and follows the principle of encapsulation.

### Abstraction

The system hides internal implementation details through classes such as `FoodManager`, `InputValidator`, and `RecommendationEngine`. The main program uses these classes without needing to directly manage their internal logic.

### Inheritance

The recommendation rules inherit from the abstract base class `RecommendationRule`. Each derived class represents a different scoring rule.

Derived rule classes include:

- `WeatherMatchRule`
- `BudgetMatchRule`
- `AffordabilityRule`
- `HealthSuitabilityRule`

### Polymorphism

The recommendation engine stores and processes different rule objects through the same abstract base class. This allows the system to evaluate multiple rules using a common interface.

This design allows new recommendation rules to be added without rewriting the entire recommendation engine.

## Recommendation Scoring System

WEASOLVE uses a rule-based scoring model with a maximum score of 100 points.

| Rule | Maximum Score | Purpose |
|---|---:|---|
| Weather Match Rule | 40 points | Checks if the food matches the current weather |
| Budget Match Rule | 25 points | Checks if the food matches the user's budget category |
| Affordability Rule | 25 points | Checks if the user has enough money to buy the food |
| Health Suitability Rule | 10 points | Gives additional score for health-related suitability |
| **Total** | **100 points** | Overall recommendation score |

Only food items with a score of 70 or higher are included in the final recommendation list.

## Database Format

The system uses `database.txt` as its external file database. Each food record follows a pipe-delimited format:

```text
ID|Name|Weather|Budget|Price|Restaurant|HealthNote
```

Example:

```text
1|Lugaw with Egg|rainy|low|55.00|Lugawan sa Kanto|Warm and easy to digest during rainy weather
```

The database contains 50 pre-existing food records, exceeding the minimum requirement of 20 records.

## Admin Panel

The system includes an admin panel protected by a PIN. The admin panel allows authorized users to:

- Add new food records
- View all food records
- Search food records
- Update existing food records
- Delete food records
- Generate a summary report
- Save changes to `database.txt`

## Input Validation

WEASOLVE includes a dedicated `InputValidator` module to reduce crashes caused by invalid input. It validates:

- Integer input
- Double input
- Empty text input
- Weather category input
- Budget category input
- Menu choices

The system also uses input stream recovery techniques such as clearing failed input states and flushing invalid buffer contents.

## Technologies Used

- C++
- Standard Template Library vector
- File handling using `ifstream` and `ofstream`
- Object-oriented programming
- Console-based user interface
- Pipe-delimited text database

## How to Compile and Run

### Compile

Using g++:

```bash
g++ -std=c++11 -Wall -Wextra -pedantic *.cpp -o weasolve
```

### Run on Linux or macOS

```bash
./weasolve
```

### Run on Windows

```bash
weasolve.exe
```

## Sample User Flow

1. The user opens the WEASOLVE system.
2. The user selects the recommendation option.
3. The system asks for weather, budget level, available money, and health preference.
4. The recommendation engine evaluates all food records.
5. The system displays ranked food recommendations with scores and explanations.
6. The user may add selected results to favorites.
7. The user may return to the main menu or exit the program.

## Academic Source Basis

The project applies concepts from CC103 lessons, including:

| Topic | Application in WEASOLVE |
|---|---|
| Topic 5 - Decision Control Basics | Menu choices, validation decisions, conditional checking |
| Topic 6 - Guard Clauses | Early validation returns and error prevention |
| Topic 7 - Advanced Boolean Logic | Multiple condition checks using logical operators |
| Topic 8 - Looping Structures | Menu loops, record traversal, repeated input prompts |
| Topic 10 - Functions and Modular Program Design | Separation of tasks into reusable functions |
| Topic 11 - Structs and STL Vectors | User preference grouping, recommendation result grouping, dynamic food collection |
| Topic 12 - Object-Oriented Programming | Classes, encapsulation, constructors, getters, setters, object interaction |
| Topic 13 - File Handling and Advanced OOP | Reading and writing records using external files, inheritance, and polymorphism |
| W3Schools C++ References | Additional reference for standard library features such as `stringstream`, `stoi`, `stod`, `std::sort`, lambda functions, `unique_ptr`, and input stream recovery |

## AI Use Disclosure

Artificial intelligence was used as a support tool during the development and documentation process of WEASOLVE. The group used AI assistance for guidance, review, debugging support, documentation improvement, README preparation, code comment refinement, and project defense preparation.

Specifically, AI was used for the following purposes:

1. Reviewing the project structure and suggesting improvements for modular organization.
2. Helping identify possible bugs, input validation risks, and file handling concerns.
3. Explaining C++ concepts such as encapsulation, polymorphism, vectors, functions, and file handling.
4. Assisting in improving the readability and academic tone of the Software Design and Analysis Document.
5. Helping prepare the README file, code comments, and project defense explanations.
6. Suggesting test cases for invalid input, corrupted records, duplicate IDs, CRUD operations, and recommendation scenarios.
7. Providing guidance on GitHub repository organization and portfolio presentation.
8. Assisting in aligning project explanations with the CC103 course topics and final project rubric.

The group did not use AI as a replacement for the required programming work. The final source code, system design decisions, testing, debugging, file organization, and project submission remain the responsibility of the group members. AI was used only as a learning, review, debugging guidance, and documentation support tool.

This disclosure is included to maintain academic honesty, transparency, and responsible AI use.

## Contributors and Roles

| Member | Role | Main Responsibility |
|---|---|---|
| Paulino, Eurie V. | Project Leader | Main controller, system integration, admin panel, final defense architecture |
| Alvarez, Jerome Oliver P. | Recommendation Engine Developer | Polymorphic recommendation engine and rule systems |
| Beli, Jhon Rey B. | Entity Developer | FoodItem class, OOP design, strict encapsulation |
| Domingo, Quirc Edrian P. | CRUD Developer | FoodManager CRUD functions |
| Malabanan, Justine Lyle R. | File Handling Developer | File handling, database loading, saving, and database format |

## Project Status

Current status:

- Console application completed
- Core C++ code finalized
- External database implemented with 50 pre-existing records
- Recommendation engine completed
- Admin panel completed
- Input validation completed
- Documentation and portfolio preparation ongoing

## Future Improvements

Future improvements may include:

- Graphical user interface using C++/CLI Windows Forms
- SQL database integration
- User account system
- Persistent favorites storage
- More advanced nutrition-based filtering
- Weather API integration
- Exportable recommendation reports

## License and Academic Use

This project was created for academic purposes as a final project for CC103 - Computer Programming 2. The system is intended for educational demonstration of C++ programming, object-oriented design, file handling, and modular software development.
