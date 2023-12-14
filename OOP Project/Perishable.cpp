/***********************************************************************
// Final project Milestone 4
// Module: Perishable
// File: Perishable.cpp
// Version 1.0
// Author  Fardad Soleimanloo
// Description: Implementation of the Perishable class member functions.
// Revision History
// -----------------------------------------------------------
// Name   :    KRUTIN BHARATBHAI POLRA
// Date   :    29th November 2023
// SECTION:    OOP244-NBB
// EMAIL  :    kbpolra@myseneca.ca
// STUDENT#ID: 135416220
// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
***********************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <iomanip>
#include <fstream>
#include <string>
#include <limits>
#include "Perishable.h"
#include "Item.h"
#include "Status.h"
#include "Date.h"
#include "Utils.h"

namespace sdds {

    // Copy constructor for Perishable
    Perishable::Perishable(const Perishable& ref) {
        *this = ref;
    }

    // Copy assignment operator for Perishable
    Perishable& Perishable::operator=(const Perishable& ref) {
        if (this != &ref) {
            // Copy base class members
            Item::operator=(ref);

            // Copy Perishable-specific members
            delete[] m_handlingInstructions;
            m_handlingInstructions = nullptr;
            m_expiryDate = ref.m_expiryDate;

            if (ref.m_handlingInstructions != nullptr) {
                m_handlingInstructions = new char[strlen(ref.m_handlingInstructions) + 1];
                strcpy(m_handlingInstructions, ref.m_handlingInstructions);
            }
        }
        return *this;
    }

    // Destructor for Perishable
    Perishable::~Perishable() {
        delete[] m_handlingInstructions;
        m_handlingInstructions = nullptr;
    }

    // Accessor function to retrieve the expiry date
    const Date& Perishable::expiry() const {
        return m_expiryDate;
    }

    // Conversion operator to check if the object is valid (non-empty)
    Perishable::operator bool() const {
        return m_sku != 0;
    }

    // Read the SKU from the input stream
    int Perishable::readSku(std::istream& istr) {
        m_state.clear();
        return m_sku = ut.getint(10000, 39999, "SKU: ");
    }

    // Save the object to the output file stream
    std::ofstream& Perishable::save(std::ofstream& ofstr) const {
        if (ofstr) {
            // Save base class members
            Item::save(ofstr);

            // Save Perishable-specific members
            ofstr << '\t' << (m_handlingInstructions ? m_handlingInstructions : "") << '\t';

            // Save formatted expiry date
            Date tempobj(m_expiryDate.getYear(), m_expiryDate.getMonth(), m_expiryDate.getDay());
            tempobj.formatted(false);
            ofstr << tempobj;
        }
        return ofstr;
    }

    // Load the object from the input file stream
    std::ifstream& Perishable::load(std::ifstream& ifstr) {
        // Load base class members
        Item::load(ifstr);

        if (ifstr.fail()) {
            m_state = "Input file stream read (perishable) failed!";
        }
        else {
            // Load Perishable-specific members
            delete[] m_handlingInstructions;
            m_handlingInstructions = nullptr;

            char temp[1000];
            if (ifstr.getline(temp, 1000, '\t') && isalpha(temp[0])) {
                m_handlingInstructions = new char[strlen(temp) + 1];
                strcpy(m_handlingInstructions, temp);
            }

            // Load expiry date
            ifstr >> m_expiryDate;
            ifstr.ignore();
        }
        return ifstr;
    }

    // Display the object on the output stream
    std::ostream& Perishable::display(std::ostream& ostr) const {
        if (!m_state) {
            // Display error message if the object is in an invalid state
            ostr << m_state;
        }
        else {
            if (Item::linear()) {
                // Display base class members in a linear format
                Item::display(ostr);

                // Display handling instructions with '*' if present
                if (m_handlingInstructions && m_handlingInstructions[0] != '\0') {
                    ostr << "*";
                }
                else {
                    ostr << " ";
                }

                // Display formatted expiry date
                ostr << m_expiryDate;
            }
            else {
                // Display detailed information for non-linear format
                ostr << "Perishable ";
                Item::display(ostr);
                ostr << "Expiry date: ";
                ostr << m_expiryDate;
                std::cout << std::endl;

                // Display handling instructions if present
                if (m_handlingInstructions && m_handlingInstructions[0] != '\0') {
                    ostr << "Handling Instructions: " << m_handlingInstructions << std::endl;
                }
            }
        }
        return ostr;
    }

    Perishable* Perishable::Move() const
    {
        return new Perishable(*this);
    }

    // Read the object from the input stream
    std::istream& Perishable::read(std::istream& istr) {
        // Read base class members
        Item::read(istr);
        delete[] m_handlingInstructions;
        m_handlingInstructions = nullptr;

        // Read expiry date
        std::cout << "Expiry date (YYMMDD): ";
        istr >> m_expiryDate;
        istr.ignore();

        // Read handling instructions
        std::cout << "Handling Instructions, ENTER to skip: ";
        if (istr.peek() != '\n') {
            m_handlingInstructions = new char[1000];
            istr.getline(m_handlingInstructions, 1000);
        }
        else {
            istr.ignore();
        }

        // Set error state if reading fails
        if (istr.fail()) {
            m_state = "Perishable console date entry failed!";
        }

        return istr;
    }
}
