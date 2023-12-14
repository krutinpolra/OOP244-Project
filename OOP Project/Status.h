/***********************************************************************
// Final project Milestone 1
// Module: status
// File: status.h
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

#ifndef SDDS_STATUS_H
#define SDDS_STATUS_H
#include <iostream>

namespace sdds {

    // Declaration of the Status class
    class Status {
        char* m_objectStatus = nullptr;  // Pointer to dynamically allocated C-string holding the status message
        int m_statusCode{};               // Status code indicating the status of an object

        // Private function to set the status message
        void setStatus(char* status);

    public:
        // Constructors
        Status(char* status = nullptr);  // Constructor with an optional initial status message
        Status(const Status& src);       // Copy constructor
        Status& operator=(const Status& src);   // Copy assignment operator

        // Destructor
        ~Status();

        // Assignment operators
        Status& operator=(int code);     // Assign an integer as the status code
        Status& operator=(const char* cStr);   // Assign a C-string as the status message

        // Conversion operators
        operator int() const;            // Conversion operator to int (return status code)
        operator const char* () const;   // Conversion operator to const char* (return status message)
        operator bool() const;           // Conversion operator to bool (check if status is valid)

        // Member function to clear the status
        Status& clear();

    };

    // Overloaded stream insertion operator
    std::ostream& operator<<(std::ostream& ostr, const Status& st);
}

#endif // !SDDS_STATUS_H
