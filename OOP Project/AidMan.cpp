/***********************************************************************
// Final project Milestone 2
// Module: AidMan
// File: AidMan.cpp
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
// Include necessary header files
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <cstring>
#include <fstream>
#include <limits>

// Include custom header files
#include "AidMan.h"
#include "Utils.h"
#include "iProduct.h"
#include "Perishable.h"

using namespace std;
namespace sdds {

	// Constructor for AidMan class
	AidMan::AidMan(const char* filename) : m_main_menu("List Items\tAdd Item\tRemove Item\tUpdate Quantity\tSort\tShip Items\tNew/Open Aid Database") {
		// Initialize m_filename based on the provided parameter
		if (filename != nullptr) {
			m_filename = new char[strlen(filename) + 1];
			strcpy(m_filename, filename);
		}
		else {
			m_filename = nullptr;
		}
	}

	// Destructor for AidMan class
	AidMan::~AidMan() {

		delete[] m_filename;
		m_filename = nullptr;
		// Call the deallocate function to free allocated memory
		deallocate();
	}

	// Function to display the main menu and return the user's selection
	unsigned int AidMan::menu() const {
		// Get the current system date
		int year, month, day = 0;
		ut.getSystemDate(&year, &month, &day);

		// Display the main menu header
		cout << "Aid Management System" << endl;
		cout << "Date: " << setw(4) << year << '/' << setfill('0') << setw(2) << month << '/' << setfill('0') << setw(2) << day << endl;
		cout << "Data file: " << (m_filename ? m_filename : "No file") << endl;
		cout << "---------------------------------" << endl;

		// Run the main menu and return the user's selection
		return m_main_menu.run();
	}

	// Function to execute the main functionality of the AidMan class
	void AidMan::run() {
		unsigned int selection = 0;

		do {
			selection = menu();

			// If the user selects an action that requires a data file, check if the file is available
			if ((selection >= 1 && selection <= 6) && (m_filename == nullptr)) {
				selection = 7;  // If no file, redirect to the "New/Open Aid Database" option
			}

			// Execute the corresponding action based on the user's selection
			switch (selection) {
			case 1:
				cout << "\n****List Items****\n";
				listItemInRow();
				break;
			case 2:
				cout << "\n****Add Item****\n";
				addItems();
				break;
			case 3:
				cout << "\n****Remove Item****\n";
				remove();
				break;
			case 4:
				cout << "\n****Update Quantity****\n";
				UpdateQuantity();
				break;
			case 5:
				cout << "\n****Sort****\n";
				sort();
				break;
			case 6:
				cout << "\n****Ship Items****\n";
				shipItems();
				break;
			case 7:
				cout << "\n****New/Open Aid Database****\n";
				load("data.dat");  // Load data from the file "data.dat"
				break;
			case 0: 
				cout << "Exiting Program!\n";
				save();
				break;
			}

		} while (selection != 0);
	}

	// Function to list items based on a provided description substring
	int AidMan::list(const char* sub_desc)
	{
		int TempRowNumber = 0;  // Counter for the number of rows displayed

		// Display table header
		cout << " ROW |  SKU  | Description                         | Have | Need |  Price  | Expiry" << endl;
		cout << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;

		int i = 0;
		do {

			ProductName[i]->linear(true);
			if (sub_desc == nullptr) {
				cout << "   " << i + 1 << " | ";
				ProductName[i]->display(cout);
				TempRowNumber++;
				cout << endl;
			}
			else if (*ProductName[i] == sub_desc) {
				// If description provided, display items matching the description
				cout << "   " << i + 1 << " | ";
				ProductName[i]->display(cout);
				TempRowNumber++;
				cout << endl;
			}
			i++;
		} while (i < numOf_IProductItems);

		// Display table footer
		cout << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;

		return TempRowNumber;  // Return the total number of rows displayed
	}

	void AidMan::listItemInRow()
	{
		int TempNumber{};
		bool IS_ValidInput = true;
		int NumberOfRow = list();

		do {
			// Prompt the user to enter a row number for details
			cout << "Enter row number to display details or <ENTER> to continue:" << endl;
			cout << "> ";
			cin.ignore();

			// If user presses Enter, exit the loop
			if (cin.peek() == '\n') {
				cout << "\n";
				break;
			}

			cin >> TempNumber;
			// Check if the entered row number is valid
			if (TempNumber >= 1 && TempNumber <= NumberOfRow) {
				// Display details for the selected item
				ProductName[TempNumber - 1]->linear(false);
				ProductName[TempNumber - 1]->display(cout);
				cout << '\n' << '\n';
			}
			else {
				// Display an error message for invalid input
				cout << "Invalid input. Please enter a valid row number." << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}

			cin.get();

		} while (!IS_ValidInput);
	}

	void AidMan::addItems()
	{
		if (numOf_IProductItems >= sdds_max_num_items) {

			cout << "Database full!" << endl;
		}
		else {

			int selection{}, tempSKU{};
			iProduct* newItem = nullptr;

			if ((selection = ut.getint(0, 2, "1- Perishable\n2- Non-Perishable\n-----------------\n0- Exit\n> ")) == 0) {
				cout << "Aborted\n";
			}
			else {

				if (selection == 1) {
					// Allocate and initialize a Perishable item
					newItem = new Perishable;
				}
				else if (selection == 2) {
					// Allocate and initialize a Non-Perishable item
					newItem = new Item;
				}

				if ((search(tempSKU = newItem->readSku(cin))) != -1) {
					std::cout << "Sku: " << setw(5) << tempSKU << " is already in the system, try updating quantity instead." << endl << endl;
				}
				else {

					if (newItem) {
						cin >> *newItem;
						cout << endl;

						if (!cin.fail()) {
							if (selection == 1) {
								ProductName[numOf_IProductItems] = newItem->Move();
							}
							if (selection == 2) {
								ProductName[numOf_IProductItems] = newItem->Move();
							}
							numOf_IProductItems++;
						}
						else {
							cout << *newItem;
						}
					}
				}
				delete newItem;
				newItem = nullptr;
			}
		}

	}



	int AidMan::search(int sku) const {

		int ifMatched = -1;

		for (int i = 0; i < numOf_IProductItems; ++i) {

			if (ProductName[i]->operator== (sku)) {
				return i; // Return the index if SKU is found
			}
		}
		return ifMatched; // Return -1 if SKU is not found
	}


	void AidMan::remove(int index) {
		// Check if the provided index is valid
		if (index < 0 || index >= numOf_IProductItems) {
			cout << "Invalid index for removal." << endl;
		}
		else {
			// Delete the dynamic memory allocated for the ProductName at the given index
			delete ProductName[index];
			ProductName[index] = nullptr;

			int i{};

			// Shift the elements in the array to fill the gap left by the removed item
			for (i = index; i < (numOf_IProductItems - 1); i++) {
				// Move the item at the next index to the current index
				ProductName[i] = ProductName[i + 1]->Move();

				// Delete the dynamic memory allocated for the ProductName at the next index
				delete ProductName[i + 1];
				ProductName[i + 1] = nullptr;
			}

			// Set the last element to nullptr
			ProductName[numOf_IProductItems - 1] = nullptr;

			// Decrease the total number of items
			numOf_IProductItems--;
		}
	}

	void AidMan::remove() {
		int numListedCount{}, SKU{}, SearchIndex{};

		// Get a description from the user and list items based on the description
		cout << "Item description: ";
		cin.clear();
		cin.ignore(10000, '\n');
		char* tempCStr = ut.getString(cin, '\n');

		// If there are items listed based on the description
		if ((numListedCount = list(tempCStr)) > 0) {
			// Get the SKU from the user
			SKU = ut.getint(10000, 99999, "Enter SKU: ");

			// Search for the item with the given SKU
			if ((SearchIndex = search(SKU)) != -1) {
				// Display information about the item to be removed
				cout << "Following item will be removed: \n";
				ProductName[SearchIndex]->linear(false);
				ProductName[SearchIndex]->display(cout);
				cout << endl;

				// Confirm removal with the user
				if (ut.getint(0, 1, "Are you sure?\n1- Yes!\n0- Exit\n> ") == 1) {
					// Remove the item at the found index
					remove(SearchIndex);
					cout << "Item removed!\n\n";
				}
				else {
					cout << "Aborted!\n\n";
				}
			}
			else {
				cout << "SKU not found!";
			}

			// Deallocate memory for the temporary C-style string
			delete[] tempCStr;
		}
		else {
			cout << "No matches found!\n";
		}
	}

	void AidMan::UpdateQuantity() {

		// Variables to store user inputs and search results
		int numListedCount{}, SKU{}, SearchIndex{}, UserInput{};

		// Prompt the user to enter item description for search
		cout << "Item description: ";
		cin.clear();
		cin.ignore(10000, '\n');
		char* TempCSTR = ut.getString(cin, '\n');

		// If there are items listed based on the description
		if ((numListedCount = list(TempCSTR)) > 0) {

			// Prompt user to enter SKU for further actions
			SKU = ut.getint(10000, 99999, "Enter SKU: ");

			// Search for the SKU in the data structure
			if ((SearchIndex = search(SKU)) != -1) {

				// Prompt user to choose between adding or reducing quantity
				UserInput = ut.getint(0, 2, "1- Add\n2- Reduce\n0- Exit\n> ");

				// Process user input
				if (UserInput == 0) {
					cout << "Aborted!\n\n";
				}
				else {
					// If user chose to add quantity
					if (UserInput == 1) {

						// Check if quantity needed is already fulfilled
						if (ProductName[SearchIndex]->qtyNeeded() == ProductName[SearchIndex]->qty()) {
							cout << "Quantity Needed already fulfilled!\n\n";
						}
						else {
							// Prompt user for quantity to add and update quantity
							int temp1 = ProductName[SearchIndex]->qtyNeeded();
							int temp2 = ProductName[SearchIndex]->qty();
							int IncreaseQuantity = ut.getint(1,
								(temp1 - temp2),
								"Quantity to add: ");
							ProductName[SearchIndex]->operator+=(IncreaseQuantity);
							cout << IncreaseQuantity << " items added!\n\n";
						}
					}
					// If user chose to reduce quantity
					if (UserInput == 2) {

						// Check if quantity on hand is already zero
						if (ProductName[SearchIndex]->qty() == 0) {
							cout << "Quantity on hand is zero!\n\n";
						}
						else {
							// Prompt user for quantity to reduce and update quantity
							int DecreaseQuantity = ut.getint(1,
								ProductName[SearchIndex]->qty(),
								"Quantity to reduce: ");
							ProductName[SearchIndex]->operator-=(DecreaseQuantity);
							cout << DecreaseQuantity << " items removed!\n\n";
						}
					}
				}
			}
			else {
				// Inform the user that SKU was not found
				cout << "SKU not found!";
			}

			// Clean up dynamically allocated memory
			delete[]TempCSTR;
		}
		else {
			// Inform the user that no matches were found
			cout << "No matches found!\n";
		}
	}


	void AidMan::sort() {
		for (int i = 0; i < numOf_IProductItems; i++) {
			for (int j = 0; j < (numOf_IProductItems - i - 1); j++) {

				// Calculate the differences in quantities
				int TempVar1 = ProductName[j]->qtyNeeded() - ProductName[j]->qty();
				int TempVar2 = ProductName[j + 1]->qtyNeeded() - ProductName[j + 1]->qty();

				// If the difference for the current item is greater than the next, swap them
				if (TempVar1 < TempVar2) {

					// Swap pointers without creating temporary objects
					iProduct* temp = ProductName[j];
					ProductName[j] = ProductName[j + 1];
					ProductName[j + 1] = temp;
				}
			}
		}

		cout << "Sort completed!\n\n";
	}



	void AidMan::shipItems() {

		ofstream ShippingFile("shippingOrder.txt");


		if (!ShippingFile.is_open()) {
			cout << "Failed to open shippingOrder.txt for writing!" << endl;
		}
		else {
			int i{}, NumberOfShippedItems{};
			Date Date{};
			Date.formatted(true);

			ShippingFile << "Shipping Order, Date: " << Date << endl;


			ShippingFile << " ROW |  SKU  | Description                         | Have | Need |  Price  | Expiry" << endl;
			ShippingFile << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;


			for (i = 0; i < numOf_IProductItems; i++) {

				if (ProductName[i]->qty() == ProductName[i]->qtyNeeded()) {

					ProductName[i]->linear(true);
					ShippingFile << "   " << NumberOfShippedItems + 1 << " | ";
					ProductName[i]->display(ShippingFile);
					ShippingFile << endl;

					NumberOfShippedItems++;
					ProductName[i]->linear(false);
					remove(i);
				}
			}

			ShippingFile << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;

			ShippingFile << "\"Shipping Order for " << NumberOfShippedItems << " times saved!\"";


			ShippingFile.close();
		}
	}


	// Function to load data from a file
	bool AidMan::load(const char* fileNametoLoadData)
	{
		// Deallocate memory if m_filename already contains a value
		if (m_filename) {
			delete[] m_filename;
			m_filename = nullptr;
		}

		// Set m_filename to the provided file name
		if (fileNametoLoadData != nullptr && fileNametoLoadData[0] != '\0') {
			m_filename = new char[strlen(fileNametoLoadData) + 1];
			strcpy(m_filename, fileNametoLoadData);
		}

		// Attempt to open the file for reading
		ifstream openFile(fileNametoLoadData);

		if (!openFile.is_open()) {
			// If the file fails to open, prompt the user to create a new file or exit
			cout << "Failed to open " << fileNametoLoadData << " for reading!" << endl;
			cout << "Would you like to create a new data file?" << endl;
			cout << "1- Yes!" << endl;
			cout << "0- Exit" << endl;
			int tempvar = 0;
			cin >> tempvar;
			if (tempvar == 1)
			{
				// If the user chooses to create a new file, attempt to create it
				ofstream getDataFromFile(fileNametoLoadData);

				if (!getDataFromFile.is_open())
				{
					// If file creation fails, display an error message and return false
					cout << "Failed to create a new data file!" << endl;
					return false;
				}
				getDataFromFile.close();
			}
			return false;
		}

		numOf_IProductItems = 0;

		// Loop to read data from the file until the end is reached or the maximum number of items is reached
		while (!openFile.eof() && numOf_IProductItems < sdds_max_num_items) {

			// Check the first digit to determine the type of product (Perishable or Item)
			if (openFile.peek() >= '1' && openFile.peek() <= '3') {
				ProductName[numOf_IProductItems] = new Perishable;
			}
			else if (openFile.peek() >= '4' && openFile.peek() <= '9') {
				ProductName[numOf_IProductItems] = new Item;
			}
			else {
				// If an invalid digit is encountered, clear the file stream and ignore the current line
				openFile.clear();
				openFile.ignore(numeric_limits<streamsize>::max(), '\n');
				continue;
			}

			// Load the product data from the file
			ProductName[numOf_IProductItems]->load(openFile);

			// If the product is valid, increment the count of loaded items and save the data
			if (*ProductName[numOf_IProductItems]) {
				numOf_IProductItems++;
			}
		}

		// If there is at least one item loaded, display the file name and the number of records loaded
		if (*this) {
			cout << "Enter file name: " << m_filename << endl;
			cout << numOf_IProductItems << " records loaded!\n" << endl;
		}
		int tempcount = (numOf_IProductItems > 0);
		return tempcount;  // Return true if at least one item is loaded
	}


	// Function to save data to a file
	void AidMan::save() {
		// Check if m_filename contains a valid value
		if (m_filename) {
			// Attempt to open the file for writing
			ofstream printFile(m_filename);

			if (printFile.is_open()) {
				int i{};
				for ( i = 0; i < numOf_IProductItems; i++)
				{
					ProductName[i]->save(printFile);
					printFile << '\n';
				}
				printFile.close();  // Close the file after saving all data
			}
			else {
				// If the file fails to open, display an error message
				cout << "Failed to open " << m_filename << " for writing!" << endl;
			}
		}
	}

	// Function to deallocate memory and reset member variables
	void AidMan::deallocate() {
		for (size_t i = numOf_IProductItems; i > 0;)
		{
			--i;
			delete ProductName[i];
			ProductName[i] = nullptr;
		}
		numOf_IProductItems = 0;  // Reset the count of loaded items
	}

}