#include "type.h"
#include <iostream>
#include <string>
#include <fstream>

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
  for (int i = 0; i < graphWidth; i++) {
    if(i % (graphWidth / 3) == 0){
      cout << endl;
    }
    
    for (int j = 0; j < graphLength; j++) {
      if(j % (graphLength / 3) == 0){
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
     cout << "combination: ";
    for (int i = 0; i < r; i++) {
     
      cout << combinationArray[i] << " ";

      // write to file
      inFile << combinationArray[i] << " ";


      // write to file instead of cout
      // then reaccess from main 
      
    }
    cout << endl;
    inFile << endl;
    return;
  }
  for (int i = start; i <= end && end - i + 1 >= r - index; i++) {
    combinationArray[index] = inputArray[i];
    FindCombinations(inputArray, combinationArray, i + 1, end, index + 1, r, inFile);
  }
}
