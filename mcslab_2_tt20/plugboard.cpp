#include "errors.h"
#include "enigma.h"
#include "plugboard.h"
#include <iostream>
#include <fstream>
#include <algorithm>  //for fill_n function


using namespace std;

//Plugboard constructor
Plugboard::Plugboard(const char* filename){

  name = filename;
  fill_n(firstArrayHalf, ALPHABET_SIZE / 2, -1);
  fill_n(secondArrayHalf, ALPHABET_SIZE / 2, -1);
  fill_n(allLetters, ALPHABET_SIZE, -1);
  
  int firstArrCounter = 0;
  int secondArrCounter = 0;
  int number = -1;
  
  ifstream in;
  in.open(filename);
  ifOpenFail(in, name);
  
  in >> ws;
  in >> number;

  while(!in.eof() ){
    
    ifNonNumeric(in, "plugboard", name);

    ifNumNotInBounds(number, "plugboard", name);

    ifTooManyParameters(numberCount, "plugboard", name, INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS);

    //we fill our arrays with the inputs from the file
    //basically an implementtion of a dictionary
    if(allLetters[number] == -1){
      allLetters[number] = number;
      if(numberCount % 2 == 0){
	firstArrayHalf[firstArrCounter] = number;
	firstArrCounter++;
      } else{
	secondArrayHalf[secondArrCounter] = number;
	secondArrCounter++;
      }
      
    }
    else {
      cerr << "A letter in plugboard file " << name;
      cerr << " is mapped to itself or has multiple mappings." << endl;
      exit(IMPOSSIBLE_PLUGBOARD_CONFIGURATION);
    }

    numberCount++;
    in >> ws;
    in >> number;
    
  }
  in.close();

  //check if letters go in pairs
  if(numberCount % 2 != 0){
    cerr << "Incorrect number of parameters in plugboard file " << name << endl;
    exit(INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS);
  }
  
}

//Pllugboard member functions - swaps letters
int Plugboard::swapLetter(int letter){

  // if letter is not mapped to any other just return it
  if(allLetters[letter] != letter){
    return letter;
  }

  // letter is changed -> letters mapped to one another share the
  // same index in these 2 arrays 'firstArrayHalf' 'secondArrayHalf'
  for(int i = 0; i < ALPHABET_SIZE / 2; i++){
    if(firstArrayHalf[i] == letter)
      return secondArrayHalf[i];

    if(secondArrayHalf[i] == letter)
      return firstArrayHalf[i];
  }
  
  //should not be reached
  return letter;
}

