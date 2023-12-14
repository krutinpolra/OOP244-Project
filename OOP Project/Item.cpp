/***********************************************************************
// Final project Milestone 3
// Module: iProduct and Item
// File: item.cpp
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
// Include necessary header files
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include "Item.h"
#include "Utils.h"

// Use the sdds namespace
namespace sdds {

    // Copy constructor
    Item::Item(const Item& src) {
        *this = src;
    }

    // Copy assignment operator
    Item& Item::operator=(const Item& src) {
        if (this != &src) {
            m_price = src.m_price;
            m_qty = src.m_qty;
            m_qtyNeeded = src.m_qtyNeeded;
            m_linear = src.m_linear;
            m_state = src.m_state;
            m_sku = src.m_sku;

            // Allocate memory for the description and copy the content
            delete[] m_description;
            if (src.m_description != nullptr) {
                m_description = new char[strlen(src.m_description) + 1];
                strcpy(m_description, src.m_description);
            }
            else {
                m_description = nullptr;
            }
        }
        return *this;
    }

    // Check if the item is linear
    bool Item::linear() const {
        return m_linear;
    }

    // Destructor
    Item::~Item() {
        delete[] m_description;
        m_description = nullptr;
    }

    // Get the quantity needed
    int Item::qtyNeeded() const {
        return m_qtyNeeded;
    }

    // Get the current quantity
    int Item::qty() const {
        return m_qty;
    }

    // Convert the item to double (price)
    Item::operator double() const {
        return m_price;
    }

    // Convert the item to bool (state)
    Item::operator bool() const {
        return m_state;
    }

    // Subtract from the quantity
    int Item::operator-=(int qty) {
        if (qty > 0) {
            m_qty -= qty;
        }
        return m_qty;
    }

    // Add to the quantity
    int Item::operator+=(int qty) {
        if (qty > 0) {
            m_qty += qty;
        }
        return m_qty;
    }

    // Set the linearity of the item
    void Item::linear(bool isLinear) {
        m_linear = isLinear;
    }

    // Clear the state of the item
    Item& Item::clear() {
        m_state.clear();
        return *this;
    }

    // Check equality with SKU
    bool Item::operator==(int sku) const {
        return m_sku == sku;
    }

    // Check equality with description
    bool Item::operator==(const char* description) const {
        int tempvar1 = strlen(description);
        int tempvar2 = strlen(m_description);

        for (int i = 0; i <= tempvar2 - tempvar1; i++) {
            int j;

            for (j = 0; j < tempvar1; j++)
                if (m_description[i + j] != description[j])
                    break;

            if (j == tempvar1)
                return true;
        }

        return false;
    }

    // Save the item to an output file stream
    std::ofstream& Item::save(std::ofstream& ofstr) const {
        if (m_state) {
            ofstr << m_sku << "\t" 
                << m_description << "\t" 
                << m_qty << "\t" 
                << m_qtyNeeded << "\t" 
                << m_price;
        }
        return ofstr;
    }

    // Load the item from an input file stream
    std::ifstream& Item::load(std::ifstream& ifstr) {
        // Delete the existing description
        delete[] m_description;
        m_description = nullptr;

        // Read SKU from the file
        ifstr >> m_sku;
        if (ifstr.fail()) {
            m_state = "Input file stream read failed!";
        }
        else {
            char tempvar[2000];
            ifstr.ignore();
            ifstr.getline(tempvar, 2000, '\t');
            m_description = new char[strlen(tempvar) + 1];
            strcpy(m_description, tempvar);

            ifstr >> m_qty;
            ifstr.ignore();

            ifstr >> m_qtyNeeded;
            ifstr.ignore();

            ifstr >> m_price;
            ifstr.ignore(1);
        }
        return ifstr;
    }

    // Display the item on an output stream
    std::ostream& Item::display(std::ostream& ostr) const {
        // Check the state of the item
        if (!m_state) {
            ostr << m_state;
        }
        else {
            // Display the item based on linearity
            if (m_linear) {
                ostr << std::setw(5) << m_sku << " | "
                    << std::left << std::setw(35) << std::setfill(' ') << (std::strlen(m_description) > 35 ? std::string(m_description, 35) : m_description)
                    << " | " << std::right << std::setw(4) << m_qty << " | "
                    << std::right << std::setw(4) << m_qtyNeeded << " | "
                    << std::right << std::setw(7) << std::fixed << std::setprecision(2) << m_price << " |";
            }
            else {
                ostr << "AMA Item:" << std::endl
                    << std::setw(5) << m_sku << ": "
                    << m_description << std::endl
                    << "Quantity Needed: " << m_qtyNeeded << std::endl
                    << "Quantity Available: " << m_qty << std::endl
                    << "Unit Price: $" << std::fixed << std::setprecision(2) << m_price << std::endl
                    << "Needed Purchase Fund: $" << std::fixed << std::setprecision(2) << (m_qtyNeeded * m_price) - (m_qty * m_price) << std::endl;
            }
        }
        return ostr;
    }

    // Read the SKU from an input stream
    int Item::readSku(std::istream& istr) {
        m_state.clear();
        m_sku = ut.getint(40000, 99999, "SKU: ");

        return m_sku;
    }

    // Read the item from an input stream
    std::istream& Item::read(std::istream& istr) {
        // Delete the existing description
        delete[] m_description;
        m_description = nullptr;

        std::cout << "AMA Item:" << std::endl
            << "SKU: " << m_sku << std::endl
            << "Description: ";

        // Read the description from the input stream
        istr.ignore();
        char tempvar[2000];
        istr.getline(tempvar, 2000);
        m_description = new char[strlen(tempvar) + 1];
        strcpy(m_description, tempvar);

        // Read quantity needed and quantity on hand from the input stream
        m_qtyNeeded = ut.getint(1, 9999, "Quantity Needed: ");
        m_qty = ut.getint(0, m_qtyNeeded, "Quantity On Hand: ");

        // Read the unit price from the input stream
        m_price = ut.getdouble(0, 9999.00, "Unit Price: $");

        return istr;
    }

    Item* Item::Move() const
    {
        return new Item(*this);
    }

}
