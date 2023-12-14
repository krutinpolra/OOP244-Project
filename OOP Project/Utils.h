/***********************************************************************
// Final project Milestone 1
// Module: Utils
// File: Utils.h
// Version 1.0
// Author  Fardad Soleimanloo
// Description
//
// Revision History
// -----------------------------------------------------------
// Name   :    KRUTIN BHARATBHAI POLRA
// Date   :    26th November 2023
// SECTION:    OOP244-NBB
// EMAIL  :    kbpolra@myseneca.ca
// STUDENT#ID: 135416220
// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
***********************************************************************/

#ifndef SDDS_UTILS_H
#define SDDS_UTILS_H
#include <iostream>

namespace sdds {

    // Constant values representing a test date
    const int testYear = 2023;
    const int testMonth = 12;
    const int testDay = 9;

    // Declaration of the Utils class
    class Utils {
        bool TestVar = false;   // Test mode flag
    public:

        // Function to get the system date
        void getSystemDate(int* S_year = nullptr, int* S_month = nullptr, int* S_day = nullptr);

        // Function to get the number of days in a given month and year
        int daysOfMon(int mon, int year) const;

        // Function to set the test mode flag
        void testMode(bool testmode = true);

        // Function to allocate memory and copy a C-string
        void alocpy(char*& destination, const char* source);

        // Function to get an integer from the user with optional prompt
        int getint(const char* prompt = nullptr);

        // Function to get an integer within a specified range from the user with optional prompt and error message
        int getint(int min, int max, const char* prompt = nullptr, const char* errMes = nullptr);

        // Function to get a double from the user with optional prompt
        double getdouble(const char* prompt = nullptr);

        // Function to get a double within a specified range from the user with optional prompt and error message
        double getdouble(double min, double max, const char* prompt = nullptr, const char* errMes = nullptr);

        char* getString(std::istream& istrobj = std::cin, char deliminator = '\n');

        char* copyString(const char* tempVar);
    };

    // External declaration of the Utils instance
    extern Utils ut;
}

#endif // !SDDS_UTILS_H
