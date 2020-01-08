#include "Morse.h"

int main() {
    cout << "Usage: -m english.txt morse.txt" << endl;
    cout << "Usage: -t morse.txt english.txt" << endl;

    string mode, source, destination;
//    cin >> mode >> source >> destination;
    mode = "-m";
    source = "english_orig.txt";
    destination = "morse.txt";
//    mode = "-t";
//    source = "morse_orig.txt";
//    destination = "english.txt";

    doConversion(mode, source, destination);
    
    return 0;
}
