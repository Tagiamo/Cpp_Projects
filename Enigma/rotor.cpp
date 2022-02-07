#include "errors.h"
#include "enigma.h"
#include "rotor.h"
#include <iostream>
#include <cstring>
#include <string>
#include <cstdio>
#include <fstream>
#include <algorithm>  //for fill_n function

using namespace std;

//Rotor constructor
Rotor::Rotor(const char* filename){

  name = filename;
  fill_n(notches, ALPHABET_SIZE, -1);
  fill_n(allLetters, ALPHABET_SIZE, -1);
  
  int number = -1;
  
  ifstream in;
  in.open(filename);
  ifOpenFail(in, name);
  
  in >> ws;
  in >> number;
  
  ifFileEmpty(in, "Rotor", name, INVALID_ROTOR_MAPPING);
  
  while(!in.eof() ){
    
    ifNonNumeric(in, "rotor", name);
    
    ifNumNotInBounds(number, "rotor", name);

    //if the letter(number) has not been encountered yet and
    //we have less than 26 letters then add it to the instance
    if(allLetters[number] == -1 && numberCount < ALPHABET_SIZE){
      allLetters[number] = number;
      rotorList[numberCount] = number;
    }

    //error occurs if we have read less than 26 letters and a
    //duplicate letter appears
    else if(allLetters[number] == number && numberCount < ALPHABET_SIZE){
      cerr << "The rotor cannot be properly configured: " << name << endl;
      cerr << "A letter is mapped to itself or has multiple mappings." << endl;
      exit(INVALID_ROTOR_MAPPING);
    }

    //we are reading a notch positon if we have already read 26 letters
    else{ //sets a notch, unless the notch already exists
      if(notches[number] == -1){
	notches[number] = number;
      }
      else {
	cerr << "Notch (" << number << ") appears multiple times in ";
	cerr << "rotor file " << name << endl;
	exit(INVALID_ROTOR_MAPPING);
      }
    }

    numberCount++;
    in >> ws;
    in >> number;
    
  }
  in.close();
  
  if(numberCount < ALPHABET_SIZE){
    cerr <<"Insufficient number of letters in rotor file " << name << endl;
    exit(INVALID_ROTOR_MAPPING);
  }
}

//Rotor member function returns the letter when moving from
// the plugboard to the rotors (in terms of direction)
int Rotor::goForward(int letter){
  int index = (letter + offset) % ALPHABET_SIZE;
  return (rotorList[index] - offset + ALPHABET_SIZE) % ALPHABET_SIZE;
}

//Rotor member function returns the letter when moving from
// the rotors to the plugboard (in terms of direction)
int Rotor::goBackward(int letter){
  letter = (letter + offset) % ALPHABET_SIZE;
  int index = 0;
  
  for(int i = 0; i < ALPHABET_SIZE; i++){
    if(rotorList[i] == letter){
      index = i;
      break;
    }
  }
  
  return (index - offset + ALPHABET_SIZE) % ALPHABET_SIZE;
}


//function to read, check and set rotors' starting postitions
void readStartingPositions(const char* filename, Rotor* rotors[], int numRotors){

  string posName = filename;
  ifstream in;
  int number;
  
  in.open(filename);
  ifOpenFail(in, posName);

  //currently, if we have N rotors then we only check for
  //the first N inputs from the positions file.
  //When I added a feature to check for further postions the
  //'Correct functionality' tests appeared to always exit
  //with an error of more starting positions than rotors.
  for(int i = 0; i < numRotors - 1; i++){
    
    in >> ws;
    in >> number;
    
    if(in.eof()){
      cerr << "No starting position for rotor "<< i;
      cerr << " in rotor position file " << posName << endl;
      exit(NO_ROTOR_STARTING_POSITION);
    }
    
    ifNonNumeric(in, "positions", posName);
    
    ifNumNotInBounds(number, "positions", posName);
    
    rotors[i] -> setOffset(number);
    
  }
  
  in.close();
  
}

