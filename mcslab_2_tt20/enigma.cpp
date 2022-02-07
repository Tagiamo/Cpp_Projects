#include "errors.h"
#include "enigma.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>

using namespace std;

int const MIN_INDEX = 0;
int const MAX_INDEX = 25;

bool isNumBounded(int num){
  if(num >= MIN_INDEX && num <= MAX_INDEX){
    return true;
  }
  else {
    return false;
  }
}


void ifNonNumeric(ifstream& in, string spot, string filename){
  if(in.fail()){
    cerr << "Non-numeric character in " << spot << " file ";
    cerr << filename << endl;
    exit(NON_NUMERIC_CHARACTER);
  }
}


void ifNumNotInBounds(int num, string spot, string filename){
  if(!isNumBounded(num)){
    cerr << "Number (" << num << ") out of the allowed range in " << spot;
    cerr << " file " << filename << endl;
    exit(INVALID_INDEX);
  }
}

//'counter' - the number of processed parameters from a 'name' config file
//'spot' - stands for 'reflector'/'plugboard'
void ifTooManyParameters(int counter, string spot, string name, int exitCode){
  if(counter >= ALPHABET_SIZE){
    cerr << "Too many parameters in " << spot << " file " << name << endl;
    exit(exitCode);
  }
}


void ifFileEmpty(ifstream& in, string spot, string name, int exitCode){
  
  if(in.eof()){
    cerr << spot << " file " << name << " is empty" << endl;
    exit(exitCode);
  }
}


void ifOpenFail(ifstream& in, string name){
  if(in.fail()){
    cerr << "Error opening a config file " << name << endl;
    exit(ERROR_OPENING_CONFIGURATION_FILE);
  }
}
