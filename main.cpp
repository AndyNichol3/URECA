#include "type.h"
#include <iomanip>
#include <iostream>
#include <fstream>

// switch the length and width dimenstions

using namespace std;

int main() {
  cout << "THIS IS THE OLD INFINATE GRAPH GENERATOR" << endl;


  int mainUserLength = getUserTileLength();
  int mainUserWidth = getUserTileWidth();
  

  cout << "Length: " << mainUserLength << endl;
  cout << "Width: " << mainUserWidth << endl;
  

  float mainUserDensity = getUserDensity();
  cout << "Density: " << mainUserDensity << endl;

  cout << "total tile size = " << mainUserWidth * mainUserLength << endl;
  cout << "total tile density = "
       << mainUserWidth * mainUserLength * mainUserDensity << endl;
  cout << endl;
  cout << "---------------------------------------------" << endl;

  // --------------------------------------
  // create the graph that will store info
  // graph should a 3x3 grid of the tile size
  // ----------------------------------------

  int graphWidth = mainUserWidth * 3;
  int graphLength = mainUserLength * 3;

  int graphG[ABSOLUTE_MAX][ABSOLUTE_MAX];
  for (int i = 0; i < graphWidth; i++) {
    for (int j = 0; j < graphLength; j++) {
      graphG[i][j] = 0;
    }
  }

  // --------------------------------------
  // display the graph (turn into function)
  // ---------------------------------------

  printGraph(graphG, graphWidth, graphLength);

  // --------end display----------------

  // write checking function to check if the graph is valid
  // find each detector, create somekind of mirror graph wich is an array of
  // pairs. if the pairs of any are identical graph is not vaild do the n chose
  // r combinations

  // while loop for all n chose r combinations
  // n chose r combinations for one tile
  // translate to the big graph
  // fill in the graph by translating the 1s onto the sorrunding 8 directions
  // check if the graph is valid by checking the intersections

  int n = mainUserWidth * mainUserLength;
  int r = n * mainUserDensity;

  int sampleCombo[n];
  for (int i = 0; i < n; i++) {
    sampleCombo[i] = i;
  }

  int currentCombo[r];
  cout << "Combinations" << endl;

  // open the write file and pass into function
  // clear the file

  fstream inFile;
  // clear contents and open
  inFile.open("combo.txt", ofstream::out | ofstream::trunc);

  

  FindCombinations(sampleCombo, currentCombo, 0, n - 1, 0, r, inFile);

  inFile.close(); 
}