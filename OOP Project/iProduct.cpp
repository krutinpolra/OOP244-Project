/***********************************************************************
// Final project Milestone 3
// Module: iProduct and Item
// File: iProduct.cpp
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
#include <iostream>
#include "iProduct.h"

namespace sdds {
    // Overloaded insertion operator (<<) for output stream and iProduct
    // Calls the display member function of the iProduct interface to output the product details
    std::ostream& operator<<(std::ostream& ostr, const iProduct& iproduct) {
        iproduct.display(ostr);
        return ostr;
    }

    // Overloaded extraction operator (>>) for input stream and iProduct
    // Calls the read member function of the iProduct interface to read product details from the input stream
    std::istream& operator>>(std::istream& istr, iProduct& iproduct) {
        iproduct.read(istr);
        return istr;
    }
}
