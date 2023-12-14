/***********************************************************************
// Final project Milestone 1
// Module: status
// File: status.cpp
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

// Header inclusion to avoid warnings related to strcpy function
#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include "Status.h"

namespace sdds {

    // Constructor with an optional initial status message
    Status::Status(char* status) {
        setStatus(status);
    }

    // Copy constructor
    Status::Status(const Status& src) {
        m_objectStatus = nullptr;
        *this = src;
    }

    // Copy assignment operator
    Status& Status::operator=(const Status& src) {
        if (this != &src) {
            // Copy status code
            m_statusCode = src.m_statusCode;
            // Delete existing status message
            delete[] m_objectStatus;

            // Copy new status message if present
            if (src.m_objectStatus && src.m_objectStatus[0] != '\0') {
                m_objectStatus = new char[strlen(src.m_objectStatus) + 1];
                strcpy(m_objectStatus, src.m_objectStatus);
            }
            else {
                m_objectStatus = nullptr;
            }
        }
        return *this;
    }

    // Destructor
    Status::~Status() {
        delete[] m_objectStatus;
        m_objectStatus = nullptr;
    }

    // Private function to set the status message
    void Status::setStatus(char* status) {
        if (status && status[0] != '\0') {
            m_objectStatus = new char[strlen(status) + 1];
            strcpy(m_objectStatus, status);
            m_statusCode = 0;
        }
        else {
            m_objectStatus = nullptr;
            m_statusCode = 0;
        }
    }

    // Assignment operator to set the status code
    Status& Status::operator=(int code) {
        m_statusCode = code;
        return *this;
    }

    // Assignment operator to set the status message
    Status& Status::operator=(const char* cStr) {
        if (cStr && cStr[0] != '\0') {
            // Delete existing status message
            if (m_objectStatus && m_objectStatus[0] != '\0') {
                delete[] m_objectStatus;
                m_objectStatus = nullptr;
            }

            // Copy new status message
            m_objectStatus = new char[strlen(cStr) + 1];
            strcpy(m_objectStatus, cStr);
        }
        return *this;
    }

    // Conversion operator to int (return status code)
    Status::operator int() const {
        return m_statusCode;
    }

    // Conversion operator to const char* (return status message)
    Status::operator const char* () const {
        return m_objectStatus;
    }

    // Conversion operator to bool (check if status is valid)
    Status::operator bool() const {
        return (!m_objectStatus) ? true : false;
    }

    // Member function to clear the status
    Status& Status::clear() {
        delete[] m_objectStatus;
        m_objectStatus = nullptr;
        m_statusCode = 0;
        return *this;
    }

    // Overloaded stream insertion operator
    std::ostream& operator<<(std::ostream& ostr, const Status& st) {
        int tempcode = st;
        const char* tempdesc = st;

        // Display appropriate status message or error code
        if (!st) {
            if (tempcode != 0) {
                ostr << "ERR#" << tempcode << ": " << tempdesc;
            }
            else {
                ostr << tempdesc;
            }
        }
        return ostr;
    }
}
