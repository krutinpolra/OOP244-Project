/***********************************************************************
// Final project Milestone 2
// Module: Menu and AidMan
// File: Menu.cpp
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
// Preprocessor directive to suppress warnings related to certain functions (specific to Visual Studio)
#define _CRT_SECURE_NO_WARNINGS

// Header file inclusion for input/output operations and string manipulation
#include <iostream>
#include <cstring>

// Header file inclusions for the Menu class and utility functions
#include "Menu.h"
#include "Utils.h"

// Using the standard namespace
using namespace std;

// Declaration of the sdds namespace
namespace sdds {

	// Function to check the validity of the number of options in the menu content
	int Menu::ISvalidNumOfOption(const char* content) const {
		int charCount{};

		// Check if the content is not null and not an empty string
		char ch = 'x';
		if (content && content[0] != '\0') {

			// Loop through each character in the content
			unsigned int i{};
			for (i = 0; i <= strlen(content); i++) {
				// Count the number of tab characters ('\t') to determine the number of options
				if ((ch = content[i]) == '\t') {
					charCount++;
				}
			}
		}
		else {
			// Set charCount to -1 if the content is null or an empty string
			charCount = -1;
		}
		return (charCount + 1); // Return the total number of options
	}

	// Function to display the menu and return the user's selection
	unsigned int Menu::run() const {

		int tempvar{};

		// Check if the menu content is not null
		if (m_productMenu) {
			int menuCharCount(1);
			unsigned int i{};

			// Display each menu option with its corresponding number
			cout << menuCharCount << "- ";
			for (i = 0; i <= strlen(m_productMenu); i++) {

				// Print each character in the menu content until a tab or the end of the string is encountered
				if (m_productMenu[i] != '\t' && m_productMenu[i] != '\0') {
					cout << m_productMenu[i];
				}
				else {
					// Move to the next line after printing an option, and print the next option number
					cout << endl;
					if (m_productMenu[i] != '\0') {
						cout << ++menuCharCount << "- ";
					}
				}
			}

			// Display a separator line and the exit option
			cout << "---------------------------------" << endl;
			cout << "0- Exit" << endl;
		}
		else
			cout << "Invalid Menu!" << endl;

		// Get the user's input for menu selection
		if (m_productMenu) {
			cout << "> ";
			tempvar = ut.getint(0, ISvalidNumOfOption(m_productMenu));
		}
		else
			tempvar = 0;

		return tempvar; // Return the user's menu selection
	}

	// Constructor for the Menu class, initializes the menu with the provided content
	Menu::Menu(const char* content) {
		int tempval = ISvalidNumOfOption(content);
		// Check if the number of options is valid
		if (tempval == -1 || tempval > (NumOfOption - 1)) {
			m_productMenu = nullptr;
		}
		else {
			// Allocate memory for the menu content and copy the provided content
			m_productMenu = new char[strlen(content) + 1];
			strcpy(m_productMenu, content);
		}
	}

	// Destructor for the Menu class, deallocates memory used by the menu content
	Menu::~Menu() {
		delete[] m_productMenu;
		m_productMenu = nullptr;
	}
}
