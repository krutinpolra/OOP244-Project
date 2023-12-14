/***********************************************************************
// Final project Milestone 1
// Module: Date
// File: Date.h
// Version 1.0
// Author  Fardad Soleimanloo
// Description
// - This file contains the declaration of the Date class.
// - The Date class represents a date and provides various functionalities
//   for manipulating and working with dates.
// Revision History
// -----------------------------------------------------------
// Name   :    KRUTIN BHARATBHAI POLRA
// Date   :    11th November 2023
// SECTION:    OOP244-NBB
// EMAIL  :    kbpolra@myseneca.ca
// STUDENT#ID: 135416220
// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
***********************************************************************/

#ifndef SDDS_DATE_H
#define SDDS_DATE_H

#include <iostream>
#include "Status.h"

namespace sdds {

    // Define the maximum allowable year
    const int maxYear = 2030;

    // Declaration of the Date class
    class Date {
        int m_year{};           // Year of the date
        int m_month{};          // Month of the date
        int m_day{};            // Day of the date
        Status m_stateOfDate;   // Status of the date (valid or invalid)
        bool m_formattedDate = true; // Flag to indicate if the date should be formatted
        bool validate();        // Private function to validate the date
        bool validYear(const int& presentYear) const;   // Private function to validate the year
        bool ValidMonth() const;    // Private function to validate the month
        bool ValidDay() const;      // Private function to validate the day
        int uniqDate() const;       // Private function to generate a unique representation of the date

    public:
        // Constructors
        Date();
        Date(int year, int month, int day);

        // Comparison operators
        bool operator==(const Date& date) const;
        bool operator!=(const Date& date) const;
        bool operator<(const Date& date) const;
        bool operator>(const Date& date) const;
        bool operator<=(const Date& date) const;
        bool operator>=(const Date& date) const;

        // Accessors
        const Status& state() const;    // Get the status of the date
        Date& formatted(bool tempvar);  // Set the formatting flag
        operator bool() const;           // Conversion operator to check if the date is valid
        std::ostream& write(std::ostream& oStr = std::cout) const;   // Write the date to an output stream
        std::istream& read(std::istream& iStr = std::cin);            // Read the date from an input stream
        int getYear() const;            // Get the year
        int getMonth() const;           // Get the month
        int getDay() const;             // Get the day
    };

    // Overloaded stream insertion operator
    std::ostream& operator<<(std::ostream& oStr, const Date& dt);

    // Overloaded stream extraction operator
    std::istream& operator>>(std::istream& iStr, Date& dt);
}

#endif // !SDDS_DATE_H
