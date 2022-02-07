#include "errors.h"
#include "enigma.h"
#include "reflector.h"
#include <iostream>
#include <fstream>
#include <algorithm>  //for fill_n function

using namespace std;

//Reflector constructor
Reflector::Reflector(const char* filename){

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

  ifFileEmpty(in, "Reflector", name, INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS);
  
  while(!in.eof() ){
    
    ifNonNumeric(in, "reflector", name);

    ifNumNotInBounds(number, "reflector", name);

    ifTooManyParameters(numberCount, "reflector", name, INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS);

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
      
    } else{
      cerr << "A letter in reflector file " << name;
      cerr <<" is mapped to itself or has multiple mappings" << endl;
      exit(INVALID_REFLECTOR_MAPPING);
    }

    numberCount++;
    in >> ws;
    in >> number;
    
  }
  in.close();

  if(numberCount != ALPHABET_SIZE){
    cerr <<"Missing mappings in reflector file " << name << endl;
    exit(INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS);
  }
  
}


//Reflector member function - swaps letters
int Reflector::swapLetter(int letter){

  // letter is changed -> letters mapped to each other share the
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

