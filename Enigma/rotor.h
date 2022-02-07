#ifndef ROTOR_H
#define ROTOR_H
#include "enigma.h"
#include <string>

class Rotor{
  //counter to store the number of file parameters passed
  int numberCount = 0;

  //this is the starting position of the rotor's rim
  int offset = 0;

  //stores the name of the configuration file
  std::string name;

  //each letter is mapped the index corresponding
  //to that same letter in this list - this list is used
  //to check for multiple mapping during initialisation
  int allLetters[ALPHABET_SIZE];

  //if we have a notch at letter 'B' -> 1 then at index
  //1 in this list we will have '1'. If there is no notch
  //the value at the index will be '-1'
  int notches[ALPHABET_SIZE];

  //keeps the specific letter config for the rotor
  int rotorList[ALPHABET_SIZE];
  
 public:
  Rotor(const char* filename);

  //method used when we are going in the direction
  //of the reflector
  int goForward(int letter);

  //method used when we are returning back from
  //the reflector
  int goBackward(int letter);
  void incrementOffset() {offset = (offset + 1) % ALPHABET_SIZE; }

  void setOffset(int num) {offset = num; }

  int getCount() {return numberCount; }
  int getOffset() {return offset;}
  int getNotch(int num) {return notches[num]; }
  std::string getName() {return name;}
};


//Function to read and check the file 'filename' with starting positions and
//set the starting positions for the rotors in the list 'rotors'
void readStartingPositions(const char* filename, Rotor* rotors[], int numRotors);

#endif 
