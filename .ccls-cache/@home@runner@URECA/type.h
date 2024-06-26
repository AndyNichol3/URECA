#pragma once
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class ArrayOfPairs {
public:
  vector<pair<int, int>> neighborhood;

  bool operator==(const ArrayOfPairs &rhs) const {
    return neighborhood == rhs.neighborhood;
  }
  void sortVector() { sort(neighborhood.begin(), neighborhood.end()); }
};

// const int DETECTOR = 1;
// int NONDETECTOR = 0;
const int ABSOLUTE_MAX = 20;

int getUserTileWidth();
int getUserTileLength();
float getUserDensity();
void printGraph(int graphG[ABSOLUTE_MAX][ABSOLUTE_MAX], int graphWidth,
                int graphLength);

void FindCombinations(int inputArray[], int combinationArray[], int start,
                      int end, int index, int r, fstream &inFile);
void clearTextFile();

void generateOLDKingGrid();

void generateOLDSquareGrid();

void generateICKingGrid();

void generateICSquareGrid();