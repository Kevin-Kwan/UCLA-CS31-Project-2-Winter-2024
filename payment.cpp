// **************************************************************************
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
// **************************************************************************


// Include necessary libraries
#include <iostream>
#include <string>
#include <iomanip>
#include <map>
#include <set>

// Sales Tax Table from /Project2Instructions/Sales_Tax_Table.pdf
// State, State Tax Rate, Average Local Tax Rate, Levy, Free Tax Month, Free Tax Day Start (inclusive), Free Tax Day End (inclusive)
std::map<std::string, std::tuple<double, double, double, std::string, int, int>> salesTaxTable = {
    std::make_pair("Alabama", std::make_tuple(4.00, 5.14, 0.00, "", 0, 0)),
    std::make_pair("Alabama", std::make_tuple(4.00, 5.14, 0.00, "July", 15, 17)),
    std::make_pair("Alaska", std::make_tuple(0.00, 1.43, 0.00, "", 0, 0)),
    std::make_pair("Arizona", std::make_tuple(5.60, 2.77, 0.00, "", 0, 0)),
    std::make_pair("Arkansas", std::make_tuple(6.50, 2.93, 0.00, "August", 6, 7)),
    std::make_pair("California", std::make_tuple(7.25, 1.31, 1.00, "", 0, 0)),
    std::make_pair("Colorado", std::make_tuple(2.90, 4.73, 0.00, "", 0, 0)),
    std::make_pair("Connecticut", std::make_tuple(6.35, 0.00, 0.00, "August", 21, 27)),
    std::make_pair("Delaware", std::make_tuple(0.00, 0.00, 0.00, "", 0, 0)),
    std::make_pair("Florida", std::make_tuple(6.00, 1.05, 0.00, "", 0, 0)),
    std::make_pair("Georgia", std::make_tuple(4.00, 3.29, 0.00, "", 0, 0)),
    std::make_pair("Hawaii", std::make_tuple(4.00, 0.41, 0.00, "", 0, 0)),
    std::make_pair("Idaho", std::make_tuple(6.00, 0.03, 0.00, "", 0, 0)),
    std::make_pair("Illinois", std::make_tuple(6.25, 2.49, 0.00, "", 0, 0)),
    std::make_pair("Indiana", std::make_tuple(7.00, 0.00, 0.00, "", 0, 0)),
    std::make_pair("Iowa", std::make_tuple(6.00, 0.82, 0.00, "August", 5, 6)),
    std::make_pair("Kansas", std::make_tuple(6.50, 2.17, 0.00, "", 0, 0)),
    std::make_pair("Kentucky", std::make_tuple(6.00, 0.00, 0.00, "", 0, 0)),
    std::make_pair("Louisiana", std::make_tuple(4.45, 5.00, 0.00, "", 0, 0)),
    std::make_pair("Maine", std::make_tuple(5.50, 0.00, 0.00, "", 0, 0)),
    std::make_pair("Maryland", std::make_tuple(6.00, 0.00, 0.00, "August", 14, 20)),
    std::make_pair("Massachusetts", std::make_tuple(6.25, 0.00, 0.00, "August", 14, 15)),
    std::make_pair("Michigan", std::make_tuple(6.00, 0.00, 0.00, "", 0, 0)),
    std::make_pair("Minnesota", std::make_tuple(6.88, 0.55, 0.00, "", 0, 0)),
    std::make_pair("Mississippi", std::make_tuple(7.00, 0.07, 0.00, "July", 29, 30)),
    std::make_pair("Missouri", std::make_tuple(4.23, 3.90, 0.00, "April", 19, 25)),
    std::make_pair("Montana", std::make_tuple(0.00, 0.00, 0.00, "", 0, 0)),
    std::make_pair("Nebraska", std::make_tuple(5.50, 1.35, 0.00, "", 0, 0)),
    std::make_pair("Nevada", std::make_tuple(6.85, 1.29, 0.00, "August", 5, 7)),
    std::make_pair("New Hampshire", std::make_tuple(0.00, 0.00, 0.00, "", 0, 0)),
    std::make_pair("New Jersey", std::make_tuple(6.63, -0.03, 0.00, "", 0, 0)),
    std::make_pair("New Mexico", std::make_tuple(5.13, 2.69, 0.00, "", 0, 0)),
    std::make_pair("New York", std::make_tuple(4.00, 4.49, 0.00, "", 0, 0)),
    std::make_pair("North Carolina", std::make_tuple(4.75, 2.22, 0.00, "", 0, 0)),
    std::make_pair("North Dakota", std::make_tuple(5.00, 1.85, 0.00, "", 0, 0)),
    std::make_pair("Ohio", std::make_tuple(5.75, 1.42, 0.00, "August", 5, 7)),
    std::make_pair("Oklahoma", std::make_tuple(4.50, 4.42, 0.00, "August", 6, 8)),
    std::make_pair("Oregon", std::make_tuple(0.00, 0.00, 0.00, "", 0, 0)),
    std::make_pair("Pennsylvania", std::make_tuple(6.00, 0.34, 0.00, "", 0, 0)),
    std::make_pair("Rhode Island", std::make_tuple(7.00, 0.00, 0.00, "", 0, 0)),
    std::make_pair("South Carolina", std::make_tuple(6.00, 1.43, 0.00, "August", 5, 7)),
    std::make_pair("South Dakota", std::make_tuple(4.50, 1.90, 0.00, "", 0, 0)),
    std::make_pair("Tennessee", std::make_tuple(7.00, 2.47, 0.00, "July", 29, 31)),
    std::make_pair("Texas", std::make_tuple(6.25, 1.94, 0.00, "August", 5, 7)),
    std::make_pair("Utah", std::make_tuple(5.95, 0.99, 1.25, "", 0, 0)),
    std::make_pair("Vermont", std::make_tuple(6.00, 0.18, 0.00, "", 0, 0)),
    std::make_pair("Virginia", std::make_tuple(5.30, 0.35, 1.00, "", 0, 0)),
    std::make_pair("Washington", std::make_tuple(6.50, 2.67, 0.00, "", 0, 0)),
    std::make_pair("West Virginia", std::make_tuple(6.00, 0.39, 0.00, "August", 5, 7)),
    std::make_pair("Wisconsin", std::make_tuple(5.00, 0.44, 0.00, "", 0, 0)),
    std::make_pair("Wyoming", std::make_tuple(4.00, 1.36, 0.00, "", 0, 0)),
};

// Set of valid months
std::set<std::string> months = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};


void getUserInput(std::string& stateName, double& purchaseAmount, std::string& month, int& day, int& year) {
    std::cout << "State Name: ";
    std::getline(std::cin, stateName);
    std::cout << "Purchase amount: ";
    std::cin >> purchaseAmount;
    std::cout << "Provide the month: ";
    std::cin >> month;
    std::cout << "Provide the day: ";
    std::cin >> day;
    std::cout << "Provide the year: ";
    std::cin >> year;
}

bool validateInput(const std::string& stateName, double purchaseAmount, const std::string& month, int day, int year) {
    // Should be O(logn), but since the set of states is a fixed size of 50, we can consider this O(1)
    if (salesTaxTable.find(stateName) == salesTaxTable.end()) 
    {
        std::cout << "Invalid state name!\n";
        return false;
    }
    

    if (purchaseAmount <= 0) {
        std::cout << "Invalid purchase amount!\n";
        return false;
    }

    // Should be O(logn), but since the set of months is a fixed size of 12, we can consider this O(1)
    if (months.find(month) == months.end()) {
        std::cout << "Invalid month!\n";
        return false;
    }

    if (day < 1 || day > 31) {
        std::cout << "Invalid day!\n";
        return false;
    }

    if (year < 1 || year > 2025) {
        std::cout << "Invalid year!\n";
        return false;
    }

    return true;
}

double calculateTotalPayment(const std::string& stateName, double purchaseAmount, const std::string& month, int day) {
    // Should be all O(1) because we are just doing lookups
    // Get tax details
    double stateTaxRate = std::get<0>(salesTaxTable[stateName]);
    double avgLocalTaxRate = std::get<1>(salesTaxTable[stateName]);
    double levy = std::get<2>(salesTaxTable[stateName]);
    // Get free tax month and day
    std::string freeTaxMonth = std::get<3>(salesTaxTable[stateName]);
    int freeTaxDayStart = std::get<4>(salesTaxTable[stateName]);
    int freeTaxDayEnd = std::get<5>(salesTaxTable[stateName]);

    if (month == freeTaxMonth && day >= freeTaxDayStart && day <= freeTaxDayEnd) {
        // No tax applied
        return purchaseAmount;
    } else {
        // Tax applied
        return purchaseAmount + (purchaseAmount * stateTaxRate / 100) + (purchaseAmount * avgLocalTaxRate / 100) + (purchaseAmount * levy / 100);
    }
}

int main() {

    std::string stateName, month;
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

    std::cout << std::fixed << std::setprecision(2) << "Please pay a total of $" << totalPayment << "\n";
    return 0;
}