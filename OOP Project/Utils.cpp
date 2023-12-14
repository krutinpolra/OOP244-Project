/***********************************************************************
// Final project Milestone 1
// Module: Utils
// File: Utils.cpp
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

// Header inclusion to avoid warnings related to strcpy function and enable the use of some C library functions
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <cstring>
#include <ctime>
#include <string>
#include "Utils.h"

using namespace std;

namespace sdds {

    // External declaration of the Utils instance
    Utils ut;

    // Function to get an integer from the user with optional prompt
    int Utils::getint(const char* inputArray) {
        int tempvar;
        bool IfVlaidInput = false;

        do {
            if (!(cin >> tempvar)) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid Integer, retry: ";
                tempvar = -1;
            }
            else {
                IfVlaidInput = true;
            }
        } while (!IfVlaidInput);

        return tempvar;
    }

    // Function to get an integer within a specified range from the user with optional prompt and error message
    int Utils::getint(int min, int max, const char* inputArray, const char* errMes) {
        int value = 0;
        bool validInput = false;

        if (inputArray != nullptr) {
            cout << inputArray;
        }

        while (!validInput) {

            value = getint(inputArray);

            if (value < min || value > max) {
                if (errMes != nullptr) {
                    cout << errMes << ", retry: ";
                }
                else {
                    cout << "Value out of range [" << min << "<=val<=" << max << "]: ";
                }
            }
            else {
                validInput = true;
            }
        }
        return value;
    }

    // Function to get the system date
    void Utils::getSystemDate(int* S_year, int* S_month, int* S_day) {

        if (TestVar) {
            // If in test mode, return the predefined test date
            if (S_day) *S_day = testDay;
            if (S_month) *S_month = testMonth;
            if (S_year) *S_year = testYear;
        }
        else {
            // Get the current system date
            time_t S_time = std::time(NULL);
            tm S_LocalTime = *localtime(&S_time);
            if (S_day) *S_day = S_LocalTime.tm_mday;
            if (S_month) *S_month = S_LocalTime.tm_mon + 1;
            if (S_year) *S_year = S_LocalTime.tm_year + 1900;
        }
    }

    // Function to get the number of days in a given month and year
    int Utils::daysOfMon(int month, int year) const {
        int Alldays[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
        int months = (month >= 1 && month <= 12 ? month : 13) - 1;
        return Alldays[months] + int((months == 1) * ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
    }

    // Function to set the test mode flag
    void Utils::testMode(bool testmode) {
        TestVar = testmode;
    }

    // Function to allocate memory and copy a C-string
    void Utils::alocpy(char*& destination, const char* source) {
        delete[] destination;
        destination = nullptr;

        if (source && source[0] != '\0') {
            destination = new char[strlen(source) + 1];
            strcpy(destination, source);
        }
    }

    // Function to get a double from the user with optional prompt
    double Utils::getdouble(const char* prompt) {
        double tempValue{};
        bool ISvalidInput = false;

        while (!ISvalidInput) {
            if (!(std::cin >> tempValue)) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid number, retry: ";
                tempValue = -1.0;
            }
            else {
                ISvalidInput = true;
            }
        }
        return tempValue;
    }

    // Function to get a double within a specified range from the user with optional prompt and error message
    double Utils::getdouble(double min, double max, const char* prompt, const char* errMes) {

        double tempValue{};
        bool ISvalidInput = false;

        if (prompt != nullptr) {
            cout << prompt;
        }

        while (!ISvalidInput) {
            tempValue = getdouble(prompt);

            if (tempValue < min || tempValue > max) {
                if (errMes != nullptr) {
                    cout << errMes << ", retry: ";
                }
                else {
                    cout << "Value out of range [" << std::fixed << std::setprecision(2) << min << "<=val<=" << max << "]: ";
                }
            }
            else {
                ISvalidInput = true;
            }
        }
        return tempValue;
    }

    char* Utils::getString(istream& istrobj, char deliminator)
    {
        char* String{};
        string tempString;
        getline(istrobj, tempString, deliminator);
        if (istrobj) {
            String = copyString(tempString.c_str());
        }

        return String;
    }

    char* Utils::copyString(const char* p_tempVar)
    {
        char* TempStr{};
        if (p_tempVar) {
            TempStr = new char[strlen(p_tempVar) + 1];
            strcpy(TempStr, p_tempVar);
        }
        return TempStr;
    }


}
