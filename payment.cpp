// ***************************************************************
// "Sales Tax Payment Calculator"
// Written by Kevin Kwan @ Georgia Institute of Technology
// The Importance of Self-Study: To learn C++ and practice C++ programming
//
// UCLA CS31 Winter 2024 Project 2
// UCLA CS31 Winter 2024 Programming Assignment 2
// This program calculates the total payment for a purchase based on the state, purchase amount, and date of purchase.
// 
// This program is written in C++ and compiled using g++.
// Comments have been added for understanding and viewing pleasure. 
//
// I am not responsible for any mistakes or errors in this program.
// Use at your own risk.
// 
// ***************************************************************


// Include necessary libraries
using namespace std;
#include <iostream>
#include <string>
#include <iomanip>
#include <unordered_map>
#include <set>

struct SalesTaxDetails {
    double stateTaxRate;
    double avgLocalTaxRate;
    double levy;
    string freeTaxMonth;
    int freeTaxDayStart;
    int freeTaxDayEnd;
};

// Sales Tax Table from /ProjectResources/Sales_Tax_Table.pdf
// State, State Tax Rate, Average Local Tax Rate, Levy, Free Tax Month, Free Tax Day Start (inclusive), Free Tax Day End (inclusive)
unordered_map<string, SalesTaxDetails> salesTaxTable = {
    {"Alabama", {4.00, 5.14, 0.00, "", 0, 0}},
    {"Alabama", {4.00, 5.14, 0.00, "July", 15, 17}},
    {"Alaska", {0.00, 1.43, 0.00, "", 0, 0}},
    {"Arizona", {5.60, 2.77, 0.00, "", 0, 0}},
    {"Arkansas", {6.50, 2.93, 0.00, "August", 6, 7}},
    {"California", {7.25, 1.31, 1.00, "", 0, 0}},
    {"Colorado", {2.90, 4.73, 0.00, "", 0, 0}},
    {"Connecticut", {6.35, 0.00, 0.00, "August", 21, 27}},
    {"Delaware", {0.00, 0.00, 0.00, "", 0, 0}},
    {"Florida", {6.00, 1.05, 0.00, "", 0, 0}},
    {"Georgia", {4.00, 3.29, 0.00, "", 0, 0}},
    {"Hawaii", {4.00, 0.41, 0.00, "", 0, 0}},
    {"Idaho", {6.00, 0.03, 0.00, "", 0, 0}},
    {"Illinois", {6.25, 2.49, 0.00, "", 0, 0}},
    {"Indiana", {7.00, 0.00, 0.00, "", 0, 0}},
    {"Iowa", {6.00, 0.82, 0.00, "August", 5, 6}},
    {"Kansas", {6.50, 2.17, 0.00, "", 0, 0}},
    {"Kentucky", {6.00, 0.00, 0.00, "", 0, 0}},
    {"Louisiana", {4.45, 5.00, 0.00, "", 0, 0}},
    {"Maine", {5.50, 0.00, 0.00, "", 0, 0}},
    {"Maryland", {6.00, 0.00, 0.00, "August", 14, 20}},
    {"Massachusetts", {6.25, 0.00, 0.00, "August", 14, 15}},
    {"Michigan", {6.00, 0.00, 0.00, "", 0, 0}},
    {"Minnesota", {6.88, 0.55, 0.00, "", 0, 0}},
    {"Mississippi", {7.00, 0.07, 0.00, "July", 29, 30}},
    {"Missouri", {4.23, 3.90, 0.00, "April", 19, 25}},
    {"Montana", {0.00, 0.00, 0.00, "", 0, 0}},
    {"Nebraska", {5.50, 1.35, 0.00, "", 0, 0}},
    {"Nevada", {6.85, 1.29, 0.00, "August", 5, 7}},
    {"New Hampshire", {0.00, 0.00, 0.00, "", 0, 0}},
    {"New Jersey", {6.63, -0.03, 0.00, "", 0, 0}},
    {"New Mexico", {5.13, 2.69, 0.00, "", 0, 0}},
    {"New York", {4.00, 4.49, 0.00, "", 0, 0}},
    {"North Carolina", {4.75, 2.22, 0.00, "", 0, 0}},
    {"North Dakota", {5.00, 1.85, 0.00, "", 0, 0}},
    {"Ohio", {5.75, 1.42, 0.00, "August", 5, 7}},
    {"Oklahoma", {4.50, 4.42, 0.00, "August", 6, 8}},
    {"Oregon", {0.00, 0.00, 0.00, "", 0, 0}},
    {"Pennsylvania", {6.00, 0.34, 0.00, "", 0, 0}},
    {"Rhode Island", {7.00, 0.00, 0.00, "", 0, 0}},
    {"South Carolina", {6.00, 1.43, 0.00, "August", 5, 7}},
    {"South Dakota", {4.50, 1.90, 0.00, "", 0, 0}},
    {"Tennessee", {7.00, 2.47, 0.00, "July", 29, 31}},
    {"Texas", {6.25, 1.94, 0.00, "August", 5, 7}},
    {"Utah", {5.95, 0.99, 1.25, "", 0, 0}},
    {"Vermont", {6.00, 0.18, 0.00, "", 0, 0}},
    {"Virginia", {5.30, 0.35, 1.00, "", 0, 0}},
    {"Washington", {6.50, 2.67, 0.00, "", 0, 0}},
    {"West Virginia", {6.00, 0.39, 0.00, "August", 5, 7}},
    {"Wisconsin", {5.00, 0.44, 0.00, "", 0, 0}},
    {"Wyoming", {4.00, 1.36, 0.00, "", 0, 0}},
};

// Set of valid months
set<string> months = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

// This function is used to get the user input for state name, purchase amount, month, day, and year.
void getUserInput(string& stateName, double& purchaseAmount, string& month, int& day, int& year) {
    cout << "State Name: ";
    getline(cin, stateName);
    cout << "Purchase amount: ";
    cin >> purchaseAmount;
    cin.ignore();
    cout << "Provide the month: ";
    getline(cin, month);
    cout << "Provide the day: ";
    cin >> day;
    cout << "Provide the year: ";
    cin >> year;
}

// This function is used to validate the user input. It checks if the state name exists in the sales tax table,
// if the purchase amount is greater than 0, if the month is valid, if the day is between 1 and 31, and if the year is between 1 and 2025.
bool validateInput(const string& stateName, double purchaseAmount, const string& month, int day, int year) {
    // Should be O(log n), but since the set of states is a fixed size of 50, we can consider this O(1)
    if (salesTaxTable.find(stateName) == salesTaxTable.end()) 
    {
        cout << "Invalid state!\n";
        return false;
    }
    
    if (purchaseAmount <= 0) {
        cout << "Invalid amount!\n";
        return false;
    }

    // Should be O(log n), but since the set of months is a fixed size of 12, we can consider this O(1)
    if (months.find(month) == months.end()) {
        cout << "Invalid month!\n";
        return false;
    }

    if (day < 1 || day > 31) {
        cout << "Invalid day!\n";
        return false;
    }

    if (year < 1 || year > 2025) {
        cout << "Invalid year!\n";
        return false;
    }

    return true;
}


// This function is used to calculate the total payment based on the state name, purchase amount, month, and day.
// It first gets the tax details for the state. Then it checks if the purchase is made during the tax-free period.
// If it is, then no tax is applied. Otherwise, the state tax, local tax, and levy are applied to the purchase amount.
double calculateTotalPayment(const string& stateName, double purchaseAmount, const string& month, int day) {
    // Should be all O(1) because we are just doing lookups
    // Get tax details
    double stateTaxRate = salesTaxTable[stateName].stateTaxRate;
    double avgLocalTaxRate = salesTaxTable[stateName].avgLocalTaxRate;
    double levy = salesTaxTable[stateName].levy;
    // Get free tax month and day
    string freeTaxMonth = salesTaxTable[stateName].freeTaxMonth;
    int freeTaxDayStart = salesTaxTable[stateName].freeTaxDayStart;
    int freeTaxDayEnd = salesTaxTable[stateName].freeTaxDayEnd;

    if (month == freeTaxMonth && day >= freeTaxDayStart && day <= freeTaxDayEnd) {
        // No tax applied
        return purchaseAmount;
    } else {
        // Tax applied
        return purchaseAmount * (1 + stateTaxRate / 100 + avgLocalTaxRate / 100 + levy / 100);
    }
}

int main() {

    string stateName, month;
    double purchaseAmount;
    int day, year;

    // Collect all inputs from user
    getUserInput(stateName, purchaseAmount, month, day, year);

    // Validate inputs
    if (!validateInput(stateName, purchaseAmount, month, day, year)) {
        return 1;
    }

    // Calculate total payment
    double totalPayment = calculateTotalPayment(stateName, purchaseAmount, month, day);

    cout << fixed << setprecision(2) << "Please pay a total of $" << totalPayment << "\n";
    return 0;
}