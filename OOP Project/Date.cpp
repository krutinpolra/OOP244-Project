/***********************************************************************
// Final project Milestone 1
// Module: Date
// File: Date.cpp
// Version 1.0
// Author  Fardad Soleimanloo
// Description
//
// Revision History
// -----------------------------------------------------------
// Name   :    KRUTIN BHARATBHAI POLRA
// Date   :    11th November 2023
// SECTION:    OOP244-NBB
// EMAIL  :    kbpolra@myseneca.ca
// STUDENT#ID: 135416220
// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
***********************************************************************/

#include "Date.h"
#include "Utils.h"

namespace sdds {

    // Private function to validate the date
    bool Date::validate() {
        int presentYear, presentMonth, presentDay;
        ut.getSystemDate(&presentYear, &presentMonth, &presentDay);

        // Validate the year, month, and day
        bool year = validYear(presentYear);
        bool month = ValidMonth();
        bool day = ValidDay();
        bool isValid = false;

        if (year && month && day) {
            // Set the date as valid
            m_stateOfDate.clear();
            isValid = true;
        }
        else {
            // If date is invalid, set appropriate error messages and state
            if (m_year == -1 || m_month == -1 || m_day == -1) {
                m_stateOfDate = "Invalid date value";
                m_stateOfDate = 0;
            }
            else {
                isValid = false;
                if (!year) {
                    m_stateOfDate = "Invalid year in date";
                    m_stateOfDate = 1;
                }
                else {
                    if (!month) {
                        m_stateOfDate = "Invalid month in date";
                        m_stateOfDate = 2;
                    }
                    else {
                        if (!day) {
                            m_stateOfDate = "Invalid day in date";
                            m_stateOfDate = 3;
                        }
                    }
                }
            }
        }

        return isValid;
    }

    // Private function to validate the year
    bool Date::validYear(const int& presentYear) const {
        return (m_year < presentYear || m_year > maxYear) ? false : true;
    }

    // Private function to validate the month
    bool Date::ValidMonth() const {
        return (m_month < 1 || m_month > 12) ? false : true;
    }

    // Private function to validate the day
    bool Date::ValidDay() const {
        return (m_day < 1 || m_day >(ut.daysOfMon(m_month, m_year))) ? false : true;
    }

    // Private function to generate a unique representation of the date
    int Date::uniqDate() const {
        return (m_year * 372 + m_month * 31 + m_day);
    }

    // Default constructor
    Date::Date() {
        ut.getSystemDate(&m_year, &m_month, &m_day);
    }

    // Parameterized constructor
    Date::Date(int year, int month, int day) {
        m_year = year;
        m_month = month;
        m_day = day;
        validate();
    }

    // Comparison operators
    bool Date::operator==(const Date& date) const {
        return (uniqDate() == date.uniqDate());
    }

    bool Date::operator!=(const Date& date) const {
        return (uniqDate() != date.uniqDate());
    }

    bool Date::operator<(const Date& date) const {
        return (uniqDate() < date.uniqDate());
    }

    bool Date::operator>(const Date& date) const {
        return (uniqDate() > date.uniqDate());
    }

    bool Date::operator<=(const Date& date) const {
        return (uniqDate() <= date.uniqDate());
    }

    bool Date::operator>=(const Date& date) const {
        return (uniqDate() >= date.uniqDate());
    }

    // Get the status of the date
    const Status& Date::state() const {
        return m_stateOfDate;
    }

    // Set the formatting flag
    Date& Date::formatted(bool tempvar) {
        m_formattedDate = tempvar;
        return *this;
    }

    // Conversion operator to check if the date is valid
    Date::operator bool() const {
        return (m_stateOfDate);
    }

    // Write the date to an output stream
    std::ostream& Date::write(std::ostream& oStr) const {
        if (m_formattedDate) {
            oStr << m_year << "/";
            oStr.fill('0');
            oStr.width(2);
            oStr << m_month << "/";
            oStr.width(2);
            oStr << m_day;
        }
        else {
            oStr << (m_year % 100);
            oStr.width(2);
            oStr << m_month;
            oStr.width(2);
            oStr << m_day;
        }
        return oStr;
    }

    // Read the date from an input stream
    std::istream& Date::read(std::istream& iStr) {
        int value{};
        int presentYear, presentMonth, presentDay;
        ut.getSystemDate(&presentYear, &presentMonth, &presentDay);

        // Read the date value from the input stream
        if (!(iStr >> value)) {
            value = -1;
        }

        // Parse the date components
        if (value < 10000) {
            m_year = presentYear;
            m_month = int(value / 100);
            m_day = value % 100;
        }
        else {
            m_year = (value / 10000) + 2000;
            m_month = (value / 100) % 100;
            m_day = value % 100;
        }

        // Validate the date and set the input stream state accordingly
        if (!validate()) {
            iStr.setstate(std::ios::badbit);
        }

        return iStr;
    }

    // Overloaded stream insertion operator
    std::ostream& operator<<(std::ostream& oStr, const Date& date) {
        return date.write(oStr);
    }

    // Overloaded stream extraction operator
    std::istream& operator>>(std::istream& iStr, Date& date) {
        return date.read(iStr);
    }

    // Get the year
    int Date::getYear() const {
        return m_year;
    }

    // Get the month
    int Date::getMonth() const {
        return m_month;
    }

    // Get the day
    int Date::getDay() const {
        return m_day;
    }
}
