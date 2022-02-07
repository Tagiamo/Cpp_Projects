#ifndef PLUGBOARD_H
#define PLUGBOARD_H
#include "enigma.h"
#include <string>

class Plugboard{
  //counter to store the number of file parameters passed
  int numberCount = 0;
  
  //stores the name of the configuration file
  std::string name;

  //these next 2 arrays will act as a dictionary -> letters
  //which share the same index are mapped to each other
  int firstArrayHalf[ALPHABET_SIZE / 2];
  int secondArrayHalf[ALPHABET_SIZE / 2];

  //this array is used to check if a letter is mapped many times
  //if at index 'y' we find 'y' then the letter has already been mapped
  int allLetters[ALPHABET_SIZE];

public:
  Plugboard(const char* filename);

  //conducts the mapping in plugboard
  int swapLetter(int letter);

  int getCount() {return numberCount; }
};

#endif
