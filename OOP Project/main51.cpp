/***********************************************************************
// Final project Milestone 51
//
// File: main51.cpp
// Version 1.0
// Author  Fardad Soleimanloo
// Description
//
// Revision History
// -----------------------------------------------------------
// Name   :    KRUTIN BHARATBHAI POLRA
// Date   :    2nd December 2023
// SECTION:    OOP244-NBB
// EMAIL  :    kbpolra@myseneca.ca
// STUDENT#ID: 135416220
// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
***********************************************************************/
#include <iostream>
#include <fstream>
#include "AidMan.h"
#include "Utils.h"
using namespace sdds;
using namespace std;

void copyfile(const char* to, const char* from);
void displayFile(const char* file);

int main() {
   copyfile("data.dat", "data51.dat");
   ut.testMode();
   AidMan().run();
   displayFile("data.dat");
   return 0;
}

void displayFile(const char* file) {
   ifstream in(file);
   char ch;
   cout << "File: " << file << endl;
   while (in.get(ch)) cout << ch;
}

void copyfile(const char* to, const char* from) {
   std::ifstream in(from);
   std::ofstream out(to);
   char ch;
   while (in.get(ch)) out.put(ch);
}
