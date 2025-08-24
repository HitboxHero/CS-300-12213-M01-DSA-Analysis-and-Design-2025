//============================================================================
// Name        : ProjectTwoKastigar.cpp
// Author      : Alex Kastigar
// Version     : 1.0
// Description : Project Two – Course Planner (Hash Table / unordered_map)
//============================================================================


#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

// course model
struct Course {
    string courseNumber;           // e.g., "CSCI300"
    string title;                  // e.g., "Data Structures"
    vector<string> prerequisites;  // store numbers like ["CSCI200","MATH201"]
};

// trim spaces both ends
static inline string trimCopy(const string& s) {
    size_t i = 0, j = s.size();
    while (i < j && isspace(static_cast<unsigned char>(s[i]))) ++i;
    while (j > i && isspace(static_cast<unsigned char>(s[j - 1]))) --j;
    return s.substr(i, j - i);
}

// strip surrounding quotes if user pasted a path with quotes
static inline string stripQuotes(const string& s) {
    if (s.size() >= 2 && s.front() == '"' && s.back() == '"') {
        return s.substr(1, s.size() - 2);
    }
    return s;
}

// normalize a course key for hashing/sorting (upper)
static inline string normKey(string s) {
    for (char& ch : s) ch = static_cast<char>(toupper(static_cast<unsigned char>(ch)));
    return s;
}

// simple CSV split (no quoted commas in the provided input file) - seems good enough for this project
static vector<string> splitCsvLine(const string& line) {
    vector<string> parts;
    string token;
    stringstream ss(line);
    while (getline(ss, token, ',')) parts.push_back(trimCopy(token));
    if (!line.empty() && line.back() == ',') parts.push_back("");
    return parts;
}

// catalog data structure
using Catalog = unordered_map<string, Course>; // key = normalized course number

// printing helpers
static void printCourse(const Catalog& catalog, const string& rawKey) {
    string key = normKey(trimCopy(rawKey));
    auto it = catalog.find(key);
    if (it == catalog.end()) {
        cout << "Course not found.\n";
        return;
    }
    const Course& c = it->second;

    cout << c.courseNumber << ", " << c.title << "\n";

    cout << "Prerequisites: ";
    if (c.prerequisites.empty()) {
        cout << "None\n";
    }
    else {
        for (size_t i = 0; i < c.prerequisites.size(); ++i) {
            if (i) cout << ", ";
            cout << c.prerequisites[i];
        }
        cout << "\n";
    }
}

// print all courses sorted alphanumerically by courseNumber (case-insensitive)
static void printAllCoursesSorted(const Catalog& catalog) {
    if (catalog.empty()) {
        cout << "No data loaded.\n";
        return;
    }

    vector<const Course*> items;
    items.reserve(catalog.size());
    for (const auto& kv : catalog) items.push_back(&kv.second);

    auto cmp = [](const Course* a, const Course* b) {
        return normKey(a->courseNumber) < normKey(b->courseNumber);
        };
    sort(items.begin(), items.end(), cmp);

    cout << "Here is a sample schedule:\n\n";
    for (const Course* c : items) {
        cout << c->courseNumber << ", " << c->title << "\n";
    }
}

static bool loadCatalogFromFile(const string& inputName, Catalog& catalog) {
    string fileName = stripQuotes(trimCopy(inputName));
    ifstream in(fileName);
    if (!in) {
        cout << "Could not open file: " << inputName << "\n";
        return false;
    }

    catalog.clear();

    string line;
    while (getline(in, line)) {
        string s = trimCopy(line);
        if (s.empty()) continue;

        vector<string> parts = splitCsvLine(s);
        if (parts.size() < 2) continue; // ignore bad rows quietly per spec

        Course c;
        c.courseNumber = normKey(parts[0]); // store as upper so it matches menu input
        c.title = parts[1];

        for (size_t i = 2; i < parts.size(); ++i) {
            if (!parts[i].empty()) c.prerequisites.push_back(normKey(parts[i]));
        }

        catalog[c.courseNumber] = c; // overwrite on duplicate id
    }
    return true;
}

// menu ui
static void printMenu() {
    cout << "\n"
        "  1. Load Data Structure.\n"
        "  2. Print Course List.\n"
        "  3. Print Course.\n"
        "  9. Exit\n\n"
        "What would you like to do? ";
}

//============================================================================
// The one and only main() method
//============================================================================


int main() {
    cout << "Welcome to the course planner.\n\n";

    Catalog catalog;
    bool loaded = false;

    while (true) {
        printMenu();
        string choice;
        if (!getline(cin, choice)) break;
        choice = trimCopy(choice);

        if (choice == "1") {
            cout << "Please enter the file name: ";
            string fileName;
            if (!getline(cin, fileName)) break;
            loaded = loadCatalogFromFile(fileName, catalog);
        }
        else if (choice == "2") {
            if (!loaded) {
                cout << "Please load the data first (option 1).\n";
            }
            else {
                printAllCoursesSorted(catalog);
            }
        }
        else if (choice == "3") {
            if (!loaded) {
                cout << "Please load the data first (option 1).\n";
            }
            else {
                cout << "What course do you want to know about? ";
                string key;
                if (!getline(cin, key)) break;
                printCourse(catalog, key);
            }
        }
        else if (choice == "9") {
            cout << "Thank you for using the course planner!\n";
            break;
        }
        else if (!choice.empty()) {
            cout << choice << " is not a valid option.\n";
        }
    }
    return 0;
}
