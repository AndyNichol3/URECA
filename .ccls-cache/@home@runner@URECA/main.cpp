#include <iostream>
#include "type.h"
#include <iomanip> 


using namespace std;

int main() {
  cout << "THIS IS THE OLD INFINATE GRAPH GENERATOR" << endl; 

  int mainUserWidth = getUserTileWidth();
  int mainUserLength = getUserTileLength();

  cout << "Width: " << mainUserWidth << endl;
  cout << "Length: " << mainUserLength << endl;

  float mainUserDensity = getUserDensity();
  cout << "Density: " << mainUserDensity << endl;

  cout << "total tile size = " << mainUserWidth * mainUserLength << endl;
  cout << "total tile density = " << mainUserWidth * mainUserLength * mainUserDensity << endl; 
  cout << endl;
  cout << "---------------------------------------------" << endl;"
}