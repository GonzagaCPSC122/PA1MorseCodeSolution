/*
@author Gina Sprint

English to morse and morse to English converter
2 possible solutions included
1. line by line then character by character
2. character by character
*/

#include "Morse.h"

int main() {
    cout << "Usage: -m english.txt morse.txt" << endl;
    cout << "Usage: -t morse.txt english.txt" << endl;
    cout << "CMD> ";

    string mode, source, destination;
    cin >> mode >> source >> destination;
    // uncomment hardcodings for fast testing (no user input required)
//    mode = "-m";
//    source = "english_orig.txt";
//    destination = "morse.txt";
//    mode = "-t";
//    source = "morse_orig.txt";
//    destination = "english.txt";

    doConversion(mode, source, destination);
    
    return 0;
}
