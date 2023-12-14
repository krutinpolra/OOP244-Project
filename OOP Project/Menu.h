/***********************************************************************
// Final project Milestone 2
// Module: Menu and AidMan
// File: Menu.h
// Version 1.0
// Description
//
// Revision History
// -----------------------------------------------------------
// Name   :    KRUTIN BHARATBHAI POLRA
// Date   :    13th November 2023
// SECTION:    OOP244-NBB
// EMAIL  :    kbpolra@myseneca.ca
// STUDENT#ID: 135416220
// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
***********************************************************************/
// Include guard to prevent multiple inclusions of the same header file
#ifndef SDDS_MENU_H
#define SDDS_MENU_H

// Declaration of the namespace
namespace sdds {

	// Constant for the maximum number of options in the menu
	const int NumOfOption = 15;

	// Declaration of the Menu class
	class Menu {

		// Pointer to a character array to store the menu content
		char* m_productMenu{};

	public:

		// Constructor: initializes the Menu object with the provided content
		Menu(const char* content);

		// Destructor: deallocates memory used by the Menu object
		~Menu();

		// Copy constructor deleted to prevent unintended copying of Menu objects
		Menu(const Menu& menu) = delete;

		// Function to display the menu and return the user's selection
		unsigned int run() const;

		// Function to check the validity of the number of options in the menu content
		int ISvalidNumOfOption(const char* content) const;
	};
}

// End of the include guard
#endif

