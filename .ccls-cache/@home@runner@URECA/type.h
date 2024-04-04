#pragma once
#include <fstream>
using namespace std; 

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
