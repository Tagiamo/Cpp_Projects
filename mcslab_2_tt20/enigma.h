#ifndef ENIGMA_H
#define ENIGMA_H
#include <fstream>
#include <string>

#define ALPHABET_SIZE   26


//Checks if the integer 'num' is between certain values
bool isNumBounded(int num);

//checks if the next element from input stream 'in' is non-numeric.
//'spot' stands for plugboard,reflector,etc. and 'filename' is the
//name of the configuration file that led to the error
void ifNonNumeric(std::ifstream& in, std::string spot, std::string filename);

//Checks if a number is between certain bounds. Produces error message
//and exits if not in bounds.
void ifNumNotInBounds(int num, std::string spot, std::string filename);

//checks if plugboard/reflector file 'name' has more parameters than needed.
//'counter' is the number of the parameter(letter). If we have more than needed
//we exit with 'exitCode'
void ifTooManyParameters(int counter, std::string spot, std::string name, int exitCode);

//checks if a file "name" of type 'spot'is empty when this is not allowed.
//Exits with 'exitCode' if so.
void ifFileEmpty(std::ifstream& in, std::string spot, std::string name, int exitCode);

//outputs error message if error encountered opening a file using input stream 'in'
void ifOpenFail(std::ifstream& in, std::string name);

#endif
