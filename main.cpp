#include "type.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>
#include <algorithm>

// switch the length and width dimenstions

using namespace std;

int main() {

  cout << "THIS IS THE DETECTION SYSTEM GENERATOR: "<< endl; 
  cout << "enter 1-4 for choices or -1 to quit: "
  << endl << "\t1: OLD king grid" << endl << "\t2: OLA Square grid" << endl << "\t3: IC king grid" << endl << "\t4: IC Square grid" << endl;
  int userChoice = 0;
  cin >> userChoice;
  switch (userChoice){
    case -1:
      cout << "PROGRAM TERMINATED" << endl;
      exit(0);
    case 1:
      generateOLDKingGrid(); 
      break; 
    case 2:
      generateOLDSquareGrid();
      break; 
    case 3:
      generateICKingGrid(); 
      break; 
    case 4:
      generateICSquareGrid();
      break;
    default:
      cout << "invalid choice" << endl;
      exit(0);
      break;
    
  }
  return 0; 
}
//