#include "errors.h"
#include "plugboard.h"
#include "reflector.h"
#include "rotor.h"
#include "enigma.h"
#include <iostream>
#include <fstream>


using namespace std;

int const MIN_CL_ARGUMENTS = 4;

int main(int argc, char** argv){

  // we need at least a plugboard, reflector, starting positions, as specified.
  // i.e. argc is at least 4 since the executable file is counted as well.
  if(argc < MIN_CL_ARGUMENTS){ 
    cerr << "Insufficient number of command line arguments given" << endl;
    exit(INSUFFICIENT_NUMBER_OF_PARAMETERS);
  }

  
  // initialise the plugboard and reflector
  Plugboard plugboard(argv[1]);
  Reflector reflector(argv[2]);
  
  // create an array of rotors - the array is of length
  // (number of rotors + 1) -> this is to deal with the case of
  // zero rotors present in the configuration files.
  // last item in the array would remain a null pointer
  int numRotors = argc - 3;
  Rotor* rotorsArray[numRotors];
  for(int i = 0; i < numRotors - 1; i++){
    rotorsArray[i] = new Rotor(argv[i + 3]);
  }

  // read, check and assign rotors' starting positions
  readStartingPositions(argv[argc - 1], rotorsArray, numRotors);
  

  
  /////// reading the message for encryption/decryption
  char letter;
  int letterNum;
  int tmp_offset;  //used to check if we have stepped on a notch
  cin >> ws;
  while(true){
    
    if((cin >> letter).eof()){
      break;
    }
    
    if(letter < 'A' || letter > 'Z'){
      cerr << letter << " is not a valid input character ";
      cerr << "(input characters must be upper case letters A-Z)!" << endl;
      exit(INVALID_INPUT_CHARACTER);
    }

    //increment right most rotor on each step (if it exists)
    if(argc > MIN_CL_ARGUMENTS){
      rotorsArray[numRotors - 2] -> incrementOffset();
    }
    
    cin >> ws;
    letterNum = ((int) letter) - (int) 'A'; //convert letter to a 0-25 number

    //entering plugboard
    letterNum = plugboard.swapLetter(letterNum);

    //entering the rotors (if there are any)
    for(int i = numRotors - 2; i >= 0; i--){
      tmp_offset = rotorsArray[i] -> getOffset();
      if(rotorsArray[i] -> getNotch(tmp_offset) == tmp_offset && i > 0){
	rotorsArray[i - 1] -> incrementOffset();
      }
      letterNum = rotorsArray[i] -> goForward(letterNum);
    }

    //reaching the reflector
    letterNum = reflector.swapLetter(letterNum);

    //returning back hrough the rotors (if there are any)
    for(int i = 0; i < numRotors - 1; i++){
      letterNum = rotorsArray[i] -> goBackward(letterNum);
    }

    //reaching the plugboard again
    letterNum = plugboard.swapLetter(letterNum);

    //encrypted/decrypted letter output
    cout << (char) ( ((int) 'A') + letterNum);
    
  }

  for(int i = 0; i < numRotors - 1; i++){
    delete rotorsArray[i];
  }
  
  return 0;
}
