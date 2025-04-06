#include <iostream>     // library for input and output
#include <fstream>      // library for file input and output
#include <cctype>       // library for character classification
#include <string>       // library for string class
#include <unistd.h>     // for realpath
#include <limits.h>     // for PATH_MAX

// Character classes
#define LETTER 0        // for letter characters
#define DIGIT 1         // for digit characters
#define UNKNOWN 99      // for unknown characters
#define END_OF_FILE -1  // for end of file marker

// Token codes
#define INT_LIT 10      // integer literal
#define IDENT 11        // identifier
#define ASSIGN_OP 20    // assignment operator
#define ADD_OP 21       // addition operator
#define SUB_OP 22       // subtraction operator
#define MULT_OP 23      // multiplication operator
#define DIV_OP 24       // division operator
#define LEFT_PAREN 25   // left parenthesis
#define RIGHT_PAREN 26  // right parenthesis

using namespace std;    // using standard namespace

// Global declarations
int charClass;          // current character class
string lexeme;          // current lexeme being built
char nextChar;          // next character in input
int nextToken;          // code for next token
ifstream inFile;        // input file stream

// Function to add character to lexeme
void addChar() {
    lexeme += nextChar; // append character to lexeme
}

// Function to get next character from input
void getChar() {
    if (inFile.get(nextChar)) {  // if successfully read character
        if (isalpha(nextChar))  // if character is letter
            charClass = LETTER;
        else if (isdigit(nextChar)) // if character is digit
            charClass = DIGIT;
        else                     // otherwise unknown
            charClass = UNKNOWN;
    } else {                    // if end of file
        charClass = END_OF_FILE;
    }
}

// Function to skip whitespace
void getNonBlank() {
    while (isspace(nextChar)) { // while character is whitespace
        getChar();              // get next character
    }
}

// Function to lookup operators
int lookup(char ch) {
    switch (ch) {              // check character
        case '(':              // left parenthesis
            addChar();
            nextToken = LEFT_PAREN;
            break;
        case ')':              // right parenthesis
            addChar();
            nextToken = RIGHT_PAREN;
            break;
        case '+':              // addition operator
            addChar();
            nextToken = ADD_OP;
            break;
        case '-':              // subtraction operator
            addChar();
            nextToken = SUB_OP;
            break;
        case '*':              // multiplication operator
            addChar();
            nextToken = MULT_OP;
            break;
        case '/':              // division operator
            addChar();
            nextToken = DIV_OP;
            break;
        case '=':              // assignment operator
            addChar();
            nextToken = ASSIGN_OP;
            break;
        default:               // unknown operator
            addChar();
            nextToken = END_OF_FILE;
            break;
    }
    return nextToken;
}

// Lexical analyzer function
int lex() {
    lexeme = "";              // initialize lexeme
    getNonBlank();            // skip whitespace

    switch (charClass) {      // based on character class
        case LETTER:          // if letter
            addChar();       //call the function to add it to the lexeme
            getChar();      // call the function to get the next char
            while (charClass == LETTER || charClass == DIGIT) { // while letter or digit
                addChar();  //call the function to add it to the lexeme
                getChar();  // call the function to get the next char
            }
            nextToken = IDENT; // set token to identifier
            break;

        case DIGIT:           // if digit
            addChar();        //call the function to add it to the lexeme
            getChar();        // call the function to get the next char
            while (charClass == DIGIT) { // while more digits
                addChar();    //call the function to add it to the lexeme
                getChar();    // call the function to get the next char
            }
            nextToken = INT_LIT; // set token to integer literal
            break;

        case UNKNOWN:         // if unknown
            lookup(nextChar); // lookup operator
            getChar();
            break;

        case END_OF_FILE:     // if end of file
            nextToken = END_OF_FILE;
            lexeme = "EOF";
            break;
    }

    // Print token information
    cout << "Next token is: " << nextToken << ", Next lexeme is: " << lexeme << endl;
    return nextToken;
}

// Main function
int main() {
    // Open input file - CHANGED THIS LINE TO FIX THE ERROR
    inFile.open("/Users/macbookpro/Downloads/front.in"); // absolute path to input file
    
    if (!inFile.is_open()) {  // if file didn't open
        cout << "ERROR - cannot open front.in" << endl; // print error
        return 1;             // return error code
    }

    getChar();               // read first character

    do {                     // loop until end of file
        lex();               // call lexical analyzer
    } while (nextToken != END_OF_FILE);

    inFile.close();          // close input file
    return 0;                // return success
}
