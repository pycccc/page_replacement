#ifndef	PAGEREPLACEMENT_H
#define PAGEREPLACEMENT_H
#include <vector>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <random>
using namespace std;

// FIFO page replacement algo
void fifo(int memSize, const vector<vector<int>>& pages, int& pageFault, int& interrupt, int& write);
// Optimal page replacement algo
void optimal(int memSize, const vector<vector<int>>& pages, int& pageFault, int& interrupt, int& write);
//Enhanced second chance page replacement algo
void enhancedSecondChance(int memSize, const vector<vector<int>>& pages, int& pageFault, int& interrupt, int& write);
// my algo
void myAlgo(int memSize, const vector<vector<int>>& pages, int& pageFault, int& interrupt, int& write);
// reference string
vector<vector<int>> randomReferenceString(int memRef_num);
vector<vector<int>> localityReferenceString(int memRef_num);
vector<vector<int>> myReferenceString(int memRef_num);

#endif

