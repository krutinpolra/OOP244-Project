/***********************************************************************
// Final project Milestone 2
// Module: AidMan
// File: AidMan.h
// Version 1.0
// Author  Fardad Soleimanloo
// Description
//
// Revision History
// -----------------------------------------------------------
// Name   :    KRUTIN BHARATBHAI POLRA
// Date   :    15th November 2023
// SECTION:    OOP244-NBB
// EMAIL  :    kbpolra@myseneca.ca
// STUDENT#ID: 135416220
// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
***********************************************************************/

// Header guard to prevent multiple inclusion
#ifndef SDDS_AIDMAN_H
#define SDDS_AIDMAN_H

#include <fstream>
#include "iProduct.h"
#include "Menu.h"

// Maximum number of items in the AidMan
const int sdds_max_num_items = 100;

namespace sdds {

    // Declaration of the AidMan class
    class AidMan {

        char* m_filename;       // Filename for data storage
        Menu m_main_menu;       // Main menu for user interactions
        iProduct* ProductName[sdds_max_num_items]{};   // Array of pointers to iProduct objects
        int numOf_IProductItems{};   // Number of iProduct items

        // Function to display the main menu and get user input
        unsigned int menu() const;

    public:
        // Constructor
        AidMan(const char* filename = nullptr);

        // Destructor
        ~AidMan();

        // Copy constructor and copy assignment operator disabled
        AidMan(const AidMan& other) = delete;
        AidMan& operator=(const AidMan& other) = delete;

        // Function to run the AidMan application
        void run();

        // Function to list iProduct items based on a provided description substring
        int list(const char* sub_desc = nullptr);

        // Conversion operator to check if the AidMan is valid (filename is set and has iProduct items)
        operator bool() const { return m_filename && numOf_IProductItems; };

        // Search for an item by SKU and return its index in the data structure.
        // If not found, return a special value (e.g., -1).
        int search(int sku) const;

        // Remove an item at the specified index from the data structure.
        void remove(int index);

        // Prompt the user to add items to the data structure.
        void addItems();

        // Remove items from the data structure.
        void remove();

        // Display a list of items in a row.
        void listItemInRow();

        // Update the quantity of an item in the data structure.
        void UpdateQuantity();

        void sort();

        void shipItems();

    private:

        // Function to load data from a file
        bool load(const char* fileNametoLoadData);

        // Function to save data to a file
        void save();

        // Function to deallocate memory for iProduct items
        void deallocate();
    };
}

#endif // !SDDS_AIDMAN_H
