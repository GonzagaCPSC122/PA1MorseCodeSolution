/*
@author Gina Sprint

English to morse and morse to English converter
2 possible solutions included
1. line by line then character by character
2. character by character
*/

#include "Morse.h"


void initializeMorseStrings(string morseStrings[]) {
	morseStrings['A'] = ".-";
    morseStrings['B'] = "-...";
    morseStrings['C'] = "-.-.";
    morseStrings['D'] = "-..";
    morseStrings['E'] = ".";
    morseStrings['F'] = "..-.";
    morseStrings['G'] = "--.";
    morseStrings['H'] = "....";
    morseStrings['I'] = "..";
    morseStrings['J'] = ".---";
    morseStrings['K'] = "-.-";
    morseStrings['L'] = ".-..";
    morseStrings['M'] = "--";
    morseStrings['N'] = "-.";
    morseStrings['O'] = "---";
    morseStrings['P'] = ".--.";
    morseStrings['Q'] = "--.-";
    morseStrings['R'] = ".-.";
    morseStrings['S'] = "...";
    morseStrings['T'] = "-";
    morseStrings['U'] = "..-";
    morseStrings['V'] = "...-";
    morseStrings['W'] = ".--";
    morseStrings['X'] = "-..-";
    morseStrings['Y'] = "-.--";
    morseStrings['Z'] = "--..";
    morseStrings['1'] = ".----";
    morseStrings['2'] = "..---";
    morseStrings['3'] = "...--";
    morseStrings['4'] = "....-";
    morseStrings['5'] = ".....";
    morseStrings['6'] = "-....";
    morseStrings['7'] = "--...";
    morseStrings['8'] = "---..";
    morseStrings['9'] = "----.";
    morseStrings['0'] = "-----";
}

void showContentsOfFile(string filename) {
	ifstream inFile;
	openSourceFile(filename, inFile);
	string line;

	while (!inFile.eof()) {
		getline(inFile, line);
		if (inFile.good()) {
			cout << line << endl;
		}
	}
	inFile.close();
}


void openSourceFile(string filename, ifstream& inFile) {
    inFile.open(filename);
    if (!inFile.is_open()) {
        cout << "Failed to open input file " << filename << endl;
        exit(-1);
    }
}

void openDestinationFile(string filename, ofstream& outFile) {
    outFile.open(filename);
    if (!outFile.is_open()) {
        cout << "Failed to open output file " << filename << endl;
        exit(-1);
    }
}

void showResults(string sourceStr, string destinationStr, int numChars) {
	cout << endl << sourceStr << endl << endl;
	showContentsOfFile(sourceStr);
	cout << endl << destinationStr << endl << endl;
	showContentsOfFile(destinationStr);
		cout << endl << "Total characters converted successfully (including newline and white spaces): " << numChars << endl << endl;
}

void doConversion(string mode, string sourceStr, string destinationStr) {
	int numChars = 0;
    ifstream source;
    ofstream destination;
    string morseStrings[MORSE_STRINGS_ARR_SIZE];
    
	initializeMorseStrings(morseStrings);

    openSourceFile(sourceStr, source);
    openDestinationFile(destinationStr, destination);

    if (mode == "-m") {
        numChars = toMorse(source, destination, morseStrings);
    }
    else if (mode == "-t") {
        numChars = toEnglish(source, destination, morseStrings);
    }
    else {
        cout << "Unrecognized mode" << endl;
        exit(-1);
    }
    
    source.close();
    destination.close();
    
    showResults(sourceStr, destinationStr, numChars);
}

char findCharForMorse(string morseString, string morseStrings[]) {
	int i;
	for (i = 0; i < MORSE_STRINGS_ARR_SIZE; i++) {
		if (morseStrings[i] == morseString) {
			return (char) i;
		}
	}
	cout << "Unrecognzied morseString" << endl;
	exit(-1);
}

char convertToUpperCaseIfNeeded(char letter) {
	if (letter >= 'a' && letter <= 'z') {
		letter = toupper(letter);
	}
	return letter;
}

///////////////////////////
// LINE BY LINE SOLUTIONS
///////////////////////////
int toMorse(ifstream& source, ofstream& destination, string morseStrings[]) {
	char currentCharacter, prevCharacter;
	int numChars = 0;
	string line = "";

	while (!source.eof()) {
		getline(source, line);
		if (source.good()) {
			for (int i = 0; i < line.size(); i++) {
				currentCharacter = line.at(i);
				if (currentCharacter == ' ') {
					destination << " ";
					numChars++;
				}
				else {
					// conver to upper case if a lower case character
					currentCharacter = convertToUpperCaseIfNeeded(currentCharacter);
					if (currentCharacter >= 'A' && currentCharacter <= 'Z' || currentCharacter >= '0' && currentCharacter <= '9') {
						destination << morseStrings[currentCharacter] << " ";
						numChars++;
					}
				}
				prevCharacter = currentCharacter;
			}
			destination << endl;
			numChars++;
		}
	}
	return numChars;
}

int toEnglish(ifstream& source, ofstream& destination, string morseStrings[]) {
	char currentCharacter, prevCharacter;
	string line = "", currentString = "";
	int numChars = 0;

	while (!source.eof()) {
		getline(source, line);
		if (source.good()) {
			for (int i = 0; i < line.size(); i++) {
				currentCharacter = line.at(i);
				if (currentCharacter == ' ') {
					if (prevCharacter == ' ') { // actually a space
						destination << " ";
						numChars++;
					}
					else { // end of a morse string... print out character
						destination << findCharForMorse(currentString, morseStrings);
						currentString = "";
						numChars++;
					}
				}
				else {
					currentString = currentString + currentCharacter;
				}
				prevCharacter = currentCharacter;
			}
			destination << endl;
			numChars++;
		}
	}
	return numChars;
}


///////////////////////////
// CHAR BY CHAR SOLUTIONS
///////////////////////////
/*
int toMorse(ifstream& source, ofstream& destination, string morseStrings[]) {
	char currentCharacter, prevCharacter;
	bool wroteFirstMorseString = false;
	int numChars = 0;

	while (!source.eof()) {
		currentCharacter = source.get();
		if (currentCharacter == ' ') {
			destination << " ";
			numChars++;
		}
		else if (currentCharacter == '\n') {
			destination << endl;
			numChars++;
		}
		else {
			if (!wroteFirstMorseString) { // to prevent extra spaces at end of file
				wroteFirstMorseString = true;
			} 
			else if (prevCharacter != '\n') { // don't write a space if we just advanced to the next line
				destination << " ";
			}
			// conver to upper case if a lower case character
			currentCharacter = convertToUpperCaseIfNeeded(currentCharacter);
			if (currentCharacter >= 'A' && currentCharacter <= 'Z' || currentCharacter >= '0' && currentCharacter <= '9') {
				destination << morseStrings[currentCharacter];
				numChars++;
			}
		}
		prevCharacter = currentCharacter;
	}
	return numChars;
}

char findCharForMorse(string morseString, string morseStrings[]) {
	int i;
	for (i = 0; i < MORSE_STRINGS_ARR_SIZE; i++) {
		if (morseStrings[i] == morseString) {
			return (char) i;
		}
	}
	cout << "Unrecognzied morseString" << endl;
	exit(-1);
}

int toEnglish(ifstream& source, ofstream& destination, string morseStrings[]) {
	char currentCharacter, prevCharacter;
	string currentString = "";
	int numChars = 0;

	while (!source.eof()) {
		currentCharacter = source.get();
		if (currentCharacter == ' ' || currentCharacter == '\n') {
			if (prevCharacter == ' ') { // actually a space
				destination << " ";
				numChars++;
			}
			else { // end of a morse string... print out character
				destination << findCharForMorse(currentString, morseStrings);
				currentString = "";
				numChars++;
			}
			if (currentCharacter == '\n') {
				destination << endl;
				numChars++;
			}
		}
		else {
			currentString = currentString + currentCharacter;
		}
		prevCharacter = currentCharacter;
	}
	return numChars;
}
*/
