/***********************************************************************
// Final project Milestone 4
// Module: Perishable
// File: Perishable.h
// Version 1.0
// Author  Fardad Soleimanloo
// Description: Declaration of the Perishable class, derived from the Item class.
//              The Perishable class adds functionality related to perishable items,
//              including expiry date and handling instructions.
//
// Revision History
// -----------------------------------------------------------
// Name   :    KRUTIN BHARATBHAI POLRA
// Date   :    29th November 2023
// SECTION:    OOP244-NBB
// EMAIL  :    kbpolra@myseneca.ca
// STUDENT#ID: 135416220
// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
***********************************************************************/

#ifndef SDDS_PERISHABLE_H
#define SDDS_PERISHABLE_H

#include "Item.h"
#include "Date.h"

namespace sdds {

    // The Perishable class, derived from the Item class
    class Perishable : public Item {
    private:
        Date m_expiryDate{};          // Expiry date of the perishable item
        char* m_handlingInstructions{}; // Handling instructions for the item

    public:
        // Default constructor
        Perishable() = default;

        // Copy constructor
        Perishable(const Perishable& ref);

        // Destructor
        ~Perishable();

        // Copy assignment operator
        Perishable& operator=(const Perishable& ref);

        // Accessor function to retrieve the expiry date
        const Date& expiry() const;

        // Conversion operator to check if the object is valid (non-empty)
        operator bool() const;

        // Read the SKU from the input stream
        int readSku(std::istream& istr);

        // Read the object from the input stream
        std::istream& read(std::istream& istr);

        // Load the object from the input file stream
        std::ifstream& load(std::ifstream& ifstr);

        // Save the object to the output file stream
        std::ofstream& save(std::ofstream& ofstr) const;

        // Display the object on the output stream
        std::ostream& display(std::ostream& ostr) const;

        virtual Perishable* Move() const;
    
    };
}

#endif // SDDS_PERISHABLE_H
