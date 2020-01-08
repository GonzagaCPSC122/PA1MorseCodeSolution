#ifndef MORSE_H
#define MORSE_H

#include <iostream>
#include <fstream>
#include <cctype>

using namespace std;

const int MORSE_STRINGS_ARR_SIZE = 91;

void initializeMorseStrings(string morseStrings[]);
void showContentsOfFile(string filename);
void openSourceFile(string filename, ifstream& inFile);
void openDestinationFile(string filename, ofstream& outFile);
int toMorse(ifstream& source, ofstream& destination, string morseStrings[]);
char findCharForMorse(string morseString, string morseStrings[]);
int toEnglish(ifstream& source, ofstream& destination, string morseStrings[]);
void showResults(string sourceStr, string destinationStr, int numChars);
void doConversion(string mode, string sourceStr, string destinationStr);

#endif
