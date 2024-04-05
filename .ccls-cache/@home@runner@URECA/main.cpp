#include "type.h"
#include <iomanip>
#include <iostream>
#include <fstream>
#include <vector> 

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
 

  fstream read;
  read.open( "combo.txt"); 
  while(!read.eof()){
    
    vector < int > comboVector;  
    string comboString;
    string storage =""; 
    getline(read, comboString,'\n');
    int index = 0;

    // put into vector
    for(int i = 0; i < comboString.length(); i++){
      if(comboString[i] == ' '){
        //cout << "storage = " << storage << endl;
        comboVector.push_back(stoi(storage));
        storage = "";
        index++;
        continue;
      }
      storage += comboString[i];
    
    }

    // --------------
    //  display vector
    // --------------
    
/*
    for(int i = 0; i < comboVector.size(); i++){
      cout << comboVector[i] << " ";
    }
    cout << endl;

*/

    // fill in the entire array
    // graphG fill in with 1 and 0s

    

    int tempArray[mainUserWidth*mainUserLength];
    for(int i = 0; i < mainUserWidth*mainUserLength; i++){
      tempArray[i] = 0; 
    }

    for(int i = 0; i < comboVector.size(); i++){
      tempArray[comboVector[i]] = 1;
    }

    // --------------------
    // diaplay 1d array
    // --------------------

    /*
    for(int i = 0; i < mainUserWidth * mainUserLength; i++){
      cout << tempArray[i] << " ";
    }
    cout << endl; 
    */ 

    // -------end----------

    // turn temp arry into graph G 

    // OBJECTIVE: turn the 1darray into the 2d full graphG

    for(int i=0; i < graphWidth; i++){
      for(int j=0; j < graphLength; j++){
        graphG[i][j] = tempArray[i*graphLength + j];
      }
    }
    
    
    int new2dArray[mainUserWidth][mainUserLength];
    int tally = 0;
    for(int i=0; i < mainUserWidth; i++){
      for(int j=0; j < mainUserLength; j++){
        new2dArray[i][j] = tempArray[tally]; 
        tally ++; 
      }
    }

    // --------------------
    // print the 2d array
    // --------------------
    /*

    for(int i=0; i < mainUserWidth; i++){
      for(int j=0; j < mainUserLength; j++){
        cout << new2dArray[i][j] << " ";
      }
      cout << endl;
    }
  cout << " ----------------- " << endl; 

    */ 
    // ------end print-----------

    // turn tile into graph g

    // STOPPED HERE:
    // OBJECTVIE: place the tile onto the big graphG

    /*
    // print the 2d graph

    for(int i = 0; i < graphWidth; i++){
      for(int j = 0; j < graphLength; j++){

        int newI = i % mainUserWidth;
        int newJ = j % mainUserLength;
        
        graphG[i][j]= new2dArray[newI][newJ];
      }
    }

    */ 
 
    // print the graph
    printGraph(graphG, graphWidth, graphLength);

    // create copy and add the neighborhoods
    // creat graphH then add some kind of data structure to keep track of neighborhood

    // check if the graph is valid
    // bool check = checkValidOLD(graphH, graphWidth, graphLength);

    // if valid, cout
    // if(check){
      //cout << graphG and graphH
    //{

    
    
    
  }
}