/***********************************************************************
// Final project Milestone 3
// Module: iProduct and Item
// File: item.h
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

// Include guards to prevent multiple inclusions of the header file
#ifndef SDDS_ITEM_H
#define SDDS_ITEM_H

// Header file inclusions
#include <iostream>
#include "Status.h"
#include "iProduct.h"

// Declaration of the sdds namespace
namespace sdds {

    // Class definition for Item, inheriting from iProduct interface
    class Item : public iProduct {
        // Private member variables
        double m_price{};
        int m_qty{};
        int m_qtyNeeded{};
        char* m_description{};
        bool m_linear{};

    protected:
        // Protected member variables
        Status m_state{};
        int m_sku{};

        // Protected member function to check if the item is linear
        bool linear() const;

    public:
        // Default constructor
        Item() = default;
        // Copy constructor
        Item(const Item& src);
        // Copy assignment operator
        Item& operator=(const Item& src);
        // Destructor
        virtual ~Item();

        // Member functions implementing the iProduct interface
        virtual int qtyNeeded() const;
        virtual int qty() const;
        virtual operator double() const;
        virtual operator bool() const;

        // Overloaded operators
        virtual int operator-=(int qty);
        virtual int operator+=(int qty);
        virtual void linear(bool isLinear);

        // Member function to clear the item
        Item& clear();

        // Overloaded equality operators
        virtual bool operator==(int sku) const;
        virtual bool operator==(const char* description) const;

        // Member functions for file operations
        virtual std::ofstream& save(std::ofstream& ofstr) const;
        virtual std::ifstream& load(std::ifstream& ifstr);

        // Member functions for displaying and reading
        virtual std::ostream& display(std::ostream& ostr) const;
        virtual int readSku(std::istream& istr) override;
        virtual std::istream& read(std::istream& istr) override;

        virtual Item* Move() const;
    };
}

// End of the include guard
#endif // !SDDS_ITEM_H
