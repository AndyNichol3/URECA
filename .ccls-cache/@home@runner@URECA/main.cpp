// todo
  // add checking for too small of a square
  // add checking for diagonal tiling? IDK how to do this
  // add auto tile size calulator for targted density. 
// implemetn a coutner for solutions

#include "type.h"

using namespace std;

int main() {

  clearTextFile();

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