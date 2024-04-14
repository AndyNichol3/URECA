#include "type.h"
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int getUserTileWidth() {
  cout << "First: Set the tile size witdh: (enter a positive int or -1 to exit)"
       << endl;
  int userWidth = -2;
  bool userInCheck = false;
  while (!userInCheck) {
    cin >> userWidth;
    // if -1 terminate the program
    if (userWidth == -1) {
      cout << "PROGRAM TERMINATED" << endl;
      exit(0);
    }
    if (userWidth > 0 && userWidth <= ABSOLUTE_MAX) {
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

int getUserTileLength() {
  cout
      << "First: Set the tile size length: (enter a positive int or -1 to exit)"
      << endl;
  int userLength = -2;
  bool userInCheck = false;
  while (!userInCheck) {
    cin >> userLength;
    // if -1 terminate the program
    if (userLength == -1) {
      cout << "PROGRAM TERMINATED" << endl;
      exit(0);
    }
    if (userLength > 0 && userLength <= ABSOLUTE_MAX) {
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

float getUserDensity() {
  cout << "Input the target density of the graph: (enter a fraction between 0 "
          "and 1 or -1 to exit)"
       << endl;
  float userDensity = -2.0;
  string userDensityString;
  bool userInCheck = false;

  while (!userInCheck) {
    cout << "Enter Density as a fraction between 0 and 1, -1 to terminate"
         << endl;
    cin >> userDensityString;

    if (userDensity == -1) {
      cout << "PROGRAM TERMINATED" << endl;
      exit(0);
    }

    float fNumerator = 0;
    float fDenominator = 0;
    string sNumerator;
    string sDenominator;
    int switchNumOrDen = 100;

    for (int i = 0; i < userDensityString.length(); i++) {

      // cout << "letter is " << userDensityString[i] << endl;

      if (userDensityString[i] == '/') {
        // cout << "entered /" << endl;
        switchNumOrDen = i;
        continue;
      }
      if (i < switchNumOrDen) {
        // cout << "entered numerator" << endl;
        sNumerator += userDensityString[i];
        continue;
      }
      if (i > switchNumOrDen) {
        // cout << "entered denominator" << endl;
        sDenominator += userDensityString[i];
        continue;
      }
    }

    fNumerator = std::stof(sNumerator);
    fDenominator = std::stof(sDenominator);

    userDensity = float(fNumerator / fDenominator);

    if (userDensity > 0 && userDensity <= 1) {
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

void printGraph(int graphG[ABSOLUTE_MAX][ABSOLUTE_MAX], int graphWidth,
                int graphLength) {
  cout << "---------------------------------------" << endl;
  for (int i = 0; i < graphWidth; i++) {
    if (i % (graphWidth / 3) == 0) {
      cout << endl;
    }

    for (int j = 0; j < graphLength; j++) {
      if (j % (graphLength / 3) == 0) {
        cout << " |  ";
      }
      cout << graphG[i][j] << " ";
    }
    cout << endl;
  }
  cout << endl;
}

void FindCombinations(int inputArray[], int combinationArray[], int start,
                      int end, int index, int r, fstream &inFile) {

  if (index == r) {
    //  cout << "combination: ";
    for (int i = 0; i < r; i++) {

      //  cout << combinationArray[i] << " ";

      // write to file
      inFile << combinationArray[i] << " ";

      // write to file instead of cout
      // then reaccess from main
    }
    //  cout << endl;
    inFile << endl;
    return;
  }
  for (int i = start; i <= end && end - i + 1 >= r - index; i++) {
    combinationArray[index] = inputArray[i];
    FindCombinations(inputArray, combinationArray, i + 1, end, index + 1, r,
                     inFile);
  }
}
void clearTextFile() {
  fstream inFile;
  // clear contents and open
  inFile.open("combo.txt", ofstream::out | ofstream::trunc);

  inFile.close();
}

void generateOLDKingGrid() {
  cout << "THIS IS THE OLD INFINITE GRAPH GENERATOR" << endl;

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
  int mainGraphLengthWidth = mainUserWidth * mainUserLength;

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

  clearTextFile();

  fstream inFile;
  inFile.open("combo.txt");

  FindCombinations(sampleCombo, currentCombo, 0, n - 1, 0, r, inFile);

  inFile.close();

  fstream read;
  read.open("combo.txt");
  while (!read.eof()) {
    // topOfWhileLoop:

    vector<int> comboVector;
    string comboString;
    string storage = "";
    getline(read, comboString, '\n');
    int index = 0;

    // put into vector
    for (int i = 0; i < comboString.length(); i++) {
      if (comboString[i] == ' ') {
        // cout << "storage = " << storage << endl;
        // the correct code
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
    // ------end-----

    // fill in the entire array
    // graphG fill in with 1 and 0s

    // --------------------
    // generate tile into 2d array
    // --------------------

    int tempArray[mainGraphLengthWidth];

    for (int i = 0; i < mainGraphLengthWidth; i++) {
      tempArray[i] = 0;
    }
    for (int i = 0; i < comboVector.size(); i++) {
      tempArray[comboVector[i]] = 1;
    }

    // ------end-----------

    // --------------------
    // diaplay 1d array
    // --------------------

    /*


  for(int i = 0; i < mainUserWidth * mainUserLength; i++){
    cout << tempArray[i] << " ";
  }
  cout << endl;*/

    // -------end----------

    // turn temp arry into graph G

    // OBJECTIVE: turn the 1darray into the 2d full graphG

    for (int i = 0; i < graphWidth; i++) {
      for (int j = 0; j < graphLength; j++) {
        graphG[i][j] = tempArray[i * graphLength + j];
      }
    }

    int new2dArray[mainUserWidth][mainUserLength];
    int tally = 0;
    for (int i = 0; i < mainUserWidth; i++) {
      for (int j = 0; j < mainUserLength; j++) {
        new2dArray[i][j] = tempArray[tally];
        tally++;
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

    // STOPPED HERE:
    // OBJECTVIE: place the tile onto the big graphG

    //----------------------
    // create 2d graph
    // ---------------------

    // create the 2d graph

    for (int i = 0; i < graphWidth; i++) {
      for (int j = 0; j < graphLength; j++) {

        int newI = i % mainUserWidth;
        int newJ = j % mainUserLength;

        graphG[i][j] = new2dArray[newI][newJ];
      }
    }

    // ---------end---------

    // print the graph
    // printGraph(graphG, graphWidth, graphLength);

    // creat graphH then add some kind of data structure to keep track of
    // neighborhood

    // sort(arr.begin(), arr.end(), comparePairs);

    // printGraph(graphG, graphWidth, graphLength);

    ArrayOfPairs graphNeighborhoods[graphWidth][graphLength];

    // CONFIRMED == works

    // STOPPED HERE
    // PSUEDO CODE BELOW

    // create copy and add the neighborhoods

    // for all of the vertex in the graph

    for (int i = 0; i < graphWidth; i++) {
      for (int j = 0; j < graphLength; j++) {
        // if the graph index == 1
        if (graphG[i][j] == 1) {
          // create the pair
          pair<int, int> tempPair = {i, j};
          // for all 8 cardinal directions
          for (int k = -1; k < 2; k++) {
            for (int l = -1; l < 2; l++) {
              // if the index is inbounds
              if (k == 0 && l == 0) {
                continue;
              }
              if (i + k >= 0 && i + k < graphWidth && j + l >= 0 &&
                  j + l < graphLength) {
                // add the pair to the graph neighborhood .pushback
                graphNeighborhoods[i + k][j + l].neighborhood.push_back(
                    tempPair);
                // cout << "pushed back " << tempPair.first << " " <<
                // tempPair.second << " to " << i + k << " " << j + l << endl;
              }
            }
          }
        }
      }
    }

    for (auto &neighborhood : graphNeighborhoods) {
      for (auto &pair : neighborhood) {
        pair.sortVector(); // Sort the vector of pairs for each element in the
                           // neighborhood
      }
    }
    bool solution = true;

    for (int i = 2; i < graphWidth - 2; i++) {
      for (int j = 2; j < graphLength - 2; j++) {
        // for all of the vertex in the graph
        // if the graph neighborod is empty
        if (graphNeighborhoods[i][j].neighborhood.empty()) {
          // cout << i << " " << j << " : empty" << endl;

          solution = false;
          // goto topOfWhileLoop;
        }

        // for all 8 cardinal directions
        // if the index is inbounds
        // if neighborhood of the index is == to the neighboohd of cardinal
        for (int k = -2; k < 3; k++) {
          for (int l = -2; l < 3; l++) {
            // if the index is inbounds
            if (k == 0 && l == 0) {
              continue;
            }
            if (i + k >= 0 && i + k < graphWidth && j + l >= 0 && j + l) {
              if (graphNeighborhoods[i + k][j + l].neighborhood ==
                  graphNeighborhoods[i][j].neighborhood) {
                // cout << i << " " << j << " : " << i + k << " " << j + l << "
                // equal " << endl;
                solution = false;
                // goto topOfWhileLoop;
              }
            }
          }

          // direction return false/break
        }
      }

      // if true at end of loop,
      // found valid solution
      // print
    }

    if (solution) {
      cout << "Solution found" << endl;
      // print
      printGraph(graphG, graphWidth, graphLength);
    }
  }
}

void generateOLDSquareGrid() {
  cout << "THIS IS THE OLD SQUARE GRID GENERATOR" << endl;

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

  int graphWidth = mainUserWidth * 3;
  int graphLength = mainUserLength * 3;
  int mainGraphLengthWidth = mainUserWidth * mainUserLength;

  int graphG[ABSOLUTE_MAX][ABSOLUTE_MAX];
  for (int i = 0; i < graphWidth; i++) {
    for (int j = 0; j < graphLength; j++) {
      graphG[i][j] = 0;
    }
  }
  printGraph(graphG, graphWidth, graphLength);

  int n = mainUserWidth * mainUserLength;
  int r = n * mainUserDensity;

  int sampleCombo[n];
  for (int i = 0; i < n; i++) {
    sampleCombo[i] = i;
  }

  int currentCombo[r];
  cout << "Combinations" << endl;

  fstream inFile;
  // clear contents and open
  inFile.open("combo.txt", ofstream::out | ofstream::trunc);

  FindCombinations(sampleCombo, currentCombo, 0, n - 1, 0, r, inFile);

  inFile.close();

  fstream read;
  read.open("combo.txt");
  while (!read.eof()) {

    vector<int> comboVector;
    string comboString;
    string storage = "";
    getline(read, comboString, '\n');
    int index = 0;

    // put into vector
    for (int i = 0; i < comboString.length(); i++) {
      if (comboString[i] == ' ') {
        comboVector.push_back(stoi(storage));

        storage = "";
        index++;
        continue;
      }
      storage += comboString[i];
    }

    int tempArray[mainGraphLengthWidth];

    for (int i = 0; i < mainGraphLengthWidth; i++) {
      tempArray[i] = 0;
    }
    for (int i = 0; i < comboVector.size(); i++) {
      tempArray[comboVector[i]] = 1;
    }

    for (int i = 0; i < graphWidth; i++) {
      for (int j = 0; j < graphLength; j++) {
        graphG[i][j] = tempArray[i * graphLength + j];
      }
    }

    int new2dArray[mainUserWidth][mainUserLength];
    int tally = 0;
    for (int i = 0; i < mainUserWidth; i++) {
      for (int j = 0; j < mainUserLength; j++) {
        new2dArray[i][j] = tempArray[tally];
        tally++;
      }
    }

    for (int i = 0; i < graphWidth; i++) {
      for (int j = 0; j < graphLength; j++) {

        int newI = i % mainUserWidth;
        int newJ = j % mainUserLength;

        graphG[i][j] = new2dArray[newI][newJ];
      }
    }

    ArrayOfPairs graphNeighborhoods[graphWidth][graphLength];

    for (int i = 0; i < graphWidth; i++) {
      for (int j = 0; j < graphLength; j++) {
        // if the graph index == 1
        if (graphG[i][j] == 1) {
          // create the pair
          pair<int, int> tempPair = {i, j};
          // for all 8 cardinal directions
          for (int k = -1; k < 2; k++) {
            for (int l = -1; l < 2; l++) {
              // if the index is inbounds

              if (k == 0 && l == 0) {
                continue;
              }
              if (k != 0 && l != 0) {
                continue;
              }
              if (i + k >= 0 && i + k < graphWidth && j + l >= 0 &&
                  j + l < graphLength) {
                // add the pair to the graph neighborhood .pushback
                graphNeighborhoods[i + k][j + l].neighborhood.push_back(
                    tempPair);
                // cout << "pushed back " << tempPair.first << " " <<
                // tempPair.second << " to " << i + k << " " << j + l << endl;
              }
            }
          }
        }
      }
    }

    for (auto &neighborhood : graphNeighborhoods) {
      for (auto &pair : neighborhood) {
        pair.sortVector(); // Sort the vector of pairs for each element in the
                           // neighborhood
      }
    }
    bool solution = true;

    for (int i = 2; i < graphWidth - 2; i++) {
      for (int j = 2; j < graphLength - 2; j++) {
        // for all of the vertex in the graph
        // if the graph neighborod is empty
        if (graphNeighborhoods[i][j].neighborhood.empty()) {
          // cout << i << " " << j << " : empty" << endl;

          solution = false;
          // goto topOfWhileLoop;
        }

        for (int k = -2; k < 3; k++) {
          for (int l = -2; l < 3; l++) {
            // if the index is inbounds
            if (k == 0 && l == 0) {
              continue;
            }
            if (i + k >= 0 && i + k < graphWidth && j + l >= 0 && j + l) {
              if (graphNeighborhoods[i + k][j + l].neighborhood ==
                  graphNeighborhoods[i][j].neighborhood) {
                // cout << i << " " << j << " : " << i + k << " " << j + l << "
                // equal " << endl;
                solution = false;
                // goto topOfWhileLoop;
              }
            }
          }

          // direction return false/break
        }
      }
    }

    if (solution) {
      cout << "Solution found" << endl;
      printGraph(graphG, graphWidth, graphLength);
    }
  }
}

void generateICKingGrid() {
  cout << "THIS IS THE OLD INFINITE GRAPH GENERATOR" << endl;

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
  int mainGraphLengthWidth = mainUserWidth * mainUserLength;

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
  read.open("combo.txt");
  while (!read.eof()) {
    // topOfWhileLoop:

    vector<int> comboVector;
    string comboString;
    string storage = "";
    getline(read, comboString, '\n');
    int index = 0;

    // put into vector
    for (int i = 0; i < comboString.length(); i++) {
      if (comboString[i] == ' ') {
        // cout << "storage = " << storage << endl;
        // the correct code
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
    // ------end-----

    // fill in the entire array
    // graphG fill in with 1 and 0s

    // --------------------
    // generate tile into 2d array
    // --------------------

    int tempArray[mainGraphLengthWidth];

    for (int i = 0; i < mainGraphLengthWidth; i++) {
      tempArray[i] = 0;
    }
    for (int i = 0; i < comboVector.size(); i++) {
      tempArray[comboVector[i]] = 1;
    }

    // ------end-----------

    // --------------------
    // diaplay 1d array
    // --------------------

    /*


  for(int i = 0; i < mainUserWidth * mainUserLength; i++){
    cout << tempArray[i] << " ";
  }
  cout << endl;*/

    // -------end----------

    // turn temp arry into graph G

    // OBJECTIVE: turn the 1darray into the 2d full graphG

    for (int i = 0; i < graphWidth; i++) {
      for (int j = 0; j < graphLength; j++) {
        graphG[i][j] = tempArray[i * graphLength + j];
      }
    }

    int new2dArray[mainUserWidth][mainUserLength];
    int tally = 0;
    for (int i = 0; i < mainUserWidth; i++) {
      for (int j = 0; j < mainUserLength; j++) {
        new2dArray[i][j] = tempArray[tally];
        tally++;
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

    // STOPPED HERE:
    // OBJECTVIE: place the tile onto the big graphG

    //----------------------
    // create 2d graph
    // ---------------------

    // create the 2d graph

    for (int i = 0; i < graphWidth; i++) {
      for (int j = 0; j < graphLength; j++) {

        int newI = i % mainUserWidth;
        int newJ = j % mainUserLength;

        graphG[i][j] = new2dArray[newI][newJ];
      }
    }

    // ---------end---------

    // print the graph
    // printGraph(graphG, graphWidth, graphLength);

    // creat graphH then add some kind of data structure to keep track of
    // neighborhood

    // sort(arr.begin(), arr.end(), comparePairs);

    // printGraph(graphG, graphWidth, graphLength);

    ArrayOfPairs graphNeighborhoods[graphWidth][graphLength];
    // pair<int, int> tempPair;

    /*
    tempPair = {1, 1};
    graphNeighborhoods[0][0].neighborhood.push_back(tempPair);

    tempPair = {0, 1};
    graphNeighborhoods[0][0].neighborhood.push_back(tempPair);

    tempPair = {0, 1};
    graphNeighborhoods[0][1].neighborhood.push_back(tempPair);

    tempPair = {1, 1};
    graphNeighborhoods[0][1].neighborhood.push_back(tempPair);
    */

    // printGraph(graphG, graphWidth, graphLength);

    /*

    if (graphNeighborhoods[0][0].neighborhood ==
        graphNeighborhoods[0][1].neighborhood) {
      cout << "EQUAL" << endl;
    } else {
      cout << "not " << endl;
    }
    */

    // CONFIRMED == works

    // STOPPED HERE
    // PSUEDO CODE BELOW

    // create copy and add the neighborhoods

    // for all of the vertex in the graph

    for (int i = 0; i < graphWidth; i++) {
      for (int j = 0; j < graphLength; j++) {
        // if the graph index == 1
        if (graphG[i][j] == 1) {
          // create the pair
          pair<int, int> tempPair = {i, j};
          // for all 8 cardinal directions
          for (int k = -1; k < 2; k++) {
            for (int l = -1; l < 2; l++) {
              // if the index is inbounds

              if (i + k >= 0 && i + k < graphWidth && j + l >= 0 &&
                  j + l < graphLength) {
                // add the pair to the graph neighborhood .pushback
                graphNeighborhoods[i + k][j + l].neighborhood.push_back(
                    tempPair);
                // cout << "pushed back " << tempPair.first << " " <<
                // tempPair.second << " to " << i + k << " " << j + l << endl;
              }
            }
          }
        }
      }
    }

    for (auto &neighborhood : graphNeighborhoods) {
      for (auto &pair : neighborhood) {
        pair.sortVector(); // Sort the vector of pairs for each element in the
                           // neighborhood
      }
    }
    bool solution = true;

    for (int i = 2; i < graphWidth - 2; i++) {
      for (int j = 2; j < graphLength - 2; j++) {
        // for all of the vertex in the graph
        // if the graph neighborod is empty
        if (graphNeighborhoods[i][j].neighborhood.empty()) {
          // cout << i << " " << j << " : empty" << endl;

          solution = false;
          // goto topOfWhileLoop;
        }

        // for all 8 cardinal directions
        // if the index is inbounds
        // if neighborhood of the index is == to the neighboohd of cardinal
        for (int k = -2; k < 3; k++) {
          for (int l = -2; l < 3; l++) {
            // if the index is inbounds
            if (k == 0 && l == 0) {
              continue;
            }
            if (i + k >= 0 && i + k < graphWidth && j + l >= 0 && j + l) {
              if (graphNeighborhoods[i + k][j + l].neighborhood ==
                  graphNeighborhoods[i][j].neighborhood) {
                // cout << i << " " << j << " : " << i + k << " " << j + l << "
                // equal " << endl;
                solution = false;
                // goto topOfWhileLoop;
              }
            }
          }

          // direction return false/break
        }
      }

      // if true at end of loop,
      // found valid solution
      // print
    }

    if (solution) {
      cout << "Solution found" << endl;
      // print
      printGraph(graphG, graphWidth, graphLength);
    }
  }
}

void generateICSquareGrid() {
  cout << "THIS IS THE OLD SQUARE GRID GENERATOR" << endl;

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

  int graphWidth = mainUserWidth * 3;
  int graphLength = mainUserLength * 3;
  int mainGraphLengthWidth = mainUserWidth * mainUserLength;

  int graphG[ABSOLUTE_MAX][ABSOLUTE_MAX];
  for (int i = 0; i < graphWidth; i++) {
    for (int j = 0; j < graphLength; j++) {
      graphG[i][j] = 0;
    }
  }
  printGraph(graphG, graphWidth, graphLength);

  int n = mainUserWidth * mainUserLength;
  int r = n * mainUserDensity;

  int sampleCombo[n];
  for (int i = 0; i < n; i++) {
    sampleCombo[i] = i;
  }

  int currentCombo[r];
  cout << "Combinations" << endl;

  fstream inFile;
  // clear contents and open
  inFile.open("combo.txt", ofstream::out | ofstream::trunc);

  FindCombinations(sampleCombo, currentCombo, 0, n - 1, 0, r, inFile);

  inFile.close();

  fstream read;
  read.open("combo.txt");
  while (!read.eof()) {

    vector<int> comboVector;
    string comboString;
    string storage = "";
    getline(read, comboString, '\n');
    int index = 0;

    // put into vector
    for (int i = 0; i < comboString.length(); i++) {
      if (comboString[i] == ' ') {
        comboVector.push_back(stoi(storage));

        storage = "";
        index++;
        continue;
      }
      storage += comboString[i];
    }

    int tempArray[mainGraphLengthWidth];

    for (int i = 0; i < mainGraphLengthWidth; i++) {
      tempArray[i] = 0;
    }
    for (int i = 0; i < comboVector.size(); i++) {
      tempArray[comboVector[i]] = 1;
    }

    for (int i = 0; i < graphWidth; i++) {
      for (int j = 0; j < graphLength; j++) {
        graphG[i][j] = tempArray[i * graphLength + j];
      }
    }

    int new2dArray[mainUserWidth][mainUserLength];
    int tally = 0;
    for (int i = 0; i < mainUserWidth; i++) {
      for (int j = 0; j < mainUserLength; j++) {
        new2dArray[i][j] = tempArray[tally];
        tally++;
      }
    }

    for (int i = 0; i < graphWidth; i++) {
      for (int j = 0; j < graphLength; j++) {

        int newI = i % mainUserWidth;
        int newJ = j % mainUserLength;

        graphG[i][j] = new2dArray[newI][newJ];
      }
    }

    ArrayOfPairs graphNeighborhoods[graphWidth][graphLength];

    for (int i = 0; i < graphWidth; i++) {
      for (int j = 0; j < graphLength; j++) {
        // if the graph index == 1
        if (graphG[i][j] == 1) {
          // create the pair
          pair<int, int> tempPair = {i, j};
          // for all 8 cardinal directions
          for (int k = -1; k < 2; k++) {
            for (int l = -1; l < 2; l++) {
              // if the index is inbounds

              // if (k == 0 && l == 0) {
              // continue;
              //}
              if (k != 0 && l != 0) {
                continue;
              }
              if (i + k >= 0 && i + k < graphWidth && j + l >= 0 &&
                  j + l < graphLength) {
                // add the pair to the graph neighborhood .pushback
                graphNeighborhoods[i + k][j + l].neighborhood.push_back(
                    tempPair);
                // cout << "pushed back " << tempPair.first << " " <<
                // tempPair.second << " to " << i + k << " " << j + l << endl;
              }
            }
          }
        }
      }
    }

    for (auto &neighborhood : graphNeighborhoods) {
      for (auto &pair : neighborhood) {
        pair.sortVector(); // Sort the vector of pairs for each element in the
                           // neighborhood
      }
    }
    bool solution = true;

    for (int i = 2; i < graphWidth - 2; i++) {
      for (int j = 2; j < graphLength - 2; j++) {
        // for all of the vertex in the graph
        // if the graph neighborod is empty
        if (graphNeighborhoods[i][j].neighborhood.empty()) {
          // cout << i << " " << j << " : empty" << endl;

          solution = false;
          // goto topOfWhileLoop;
        }

        for (int k = -2; k < 3; k++) {
          for (int l = -2; l < 3; l++) {
            // if the index is inbounds
            if (k == 0 && l == 0) {
              continue;
            }
            if (i + k >= 0 && i + k < graphWidth && j + l >= 0 && j + l) {
              if (graphNeighborhoods[i + k][j + l].neighborhood ==
                  graphNeighborhoods[i][j].neighborhood) {
                // cout << i << " " << j << " : " << i + k << " " << j + l << "
                // equal " << endl;
                solution = false;
                // goto topOfWhileLoop;
              }
            }
          }

          // direction return false/break
        }
      }
    }

    if (solution) {
      cout << "Solution found" << endl;
      printGraph(graphG, graphWidth, graphLength);
    }
  }
}
