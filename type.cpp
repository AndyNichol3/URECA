#include <iostream>
#include "type.h"

using namespace std;

int getUserTileWidth(){
  cout<< "First: Set the tile size witdh: (enter a positive int or -1 to exit)" << endl;
  int userWidth = -2;
  bool userInCheck = false;
  while(!userInCheck){
    cin >> userWidth;
    // if -1 terminate the program
    if(userWidth == -1){
      cout << "PROGRAM TERMINATED" << endl; 
      exit(0);
    } 
    if(userWidth > 0 && userWidth <= ABSOLUTE_MAX){
      userInCheck = true;
      cout << "VALID USER IN" << endl; 
      break; 

    }

    cout << "INVALID USER IN, TRY AGAIN" << endl; 
    // clear buffer
    cin.clear();
    cin.ignore(); 
  }

  return userWidth;
}

int getUserTileLength(){
  cout<< "First: Set the tile size length: (enter a positive int or -1 to exit)" << endl;
  int userLength = -2;
  bool userInCheck = false;
  while(!userInCheck){
    cin >> userLength;
    // if -1 terminate the program
    if(userLength == -1){
      cout << "PROGRAM TERMINATED" << endl; 
      exit(0);
    } 
    if(userLength > 0 && userLength <= ABSOLUTE_MAX){
      userInCheck = true;
      cout << "VALID USER IN" << endl; 
      break; 

    }

    cout << "INVALID USER IN, TRY AGAIN" << endl; 
    // clear buffer
    cin.clear();
    cin.ignore(); 
  }

  return userLength;
}

float getUserDensity(){
  cout << "Input the target density of the graph: (enter a percentage as a decimal 0.0 to 1.0 or -1 to exit)" << endl;
  float userDensity = -2.0;
  bool userInCheck = false;
  while(!userInCheck){
    cin >> userDensity;
    // if -1 terminate the program
    if(userDensity == -1){
      cout << "PROGRAM TERMINATED" << endl;
      exit(0);
    }
    if(userDensity >= 0.0 && userDensity <= 1.0){
      userInCheck = true;
      cout << "VALID USER IN" << endl;
      break;
    }

    cout << "INVALID USER IN, TRY AGAIN" << endl;
    // clear buffer
    cin.clear();
    cin.ignore();
    
  }
  return userDensity;
}