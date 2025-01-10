#include "pageReplacement.h"
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
using namespace std;

// FIFO 
void fifo(int frameCount, const vector<vector<int>>& pages, int& pageFault, int& interrupt, int& write) {
    pageFault = 0;
    interrupt = 0;
    write = 0;

    queue<int> frame;   
    unordered_set<int> pageInMem;  
    unordered_map<int, int> modificationBits;

    for (const auto& page : pages) {
        int reference = page[0];
        int modification = page[1];
        //case 1: cant find page in mem, page fault
        if (pageInMem.find(reference) == pageInMem.end()) {  
            pageFault++;
            interrupt++;
            if (frame.size() < frameCount) {  // case 1-1 if mem is not full
                frame.push(reference);
                pageInMem.insert(reference);
            }
            else {  // case1-2 mem is full, page replacement is needed
                int victim = frame.front();   //fifo
                frame.pop();
                pageInMem.erase(victim);

                if (modificationBits[victim] == 1) {  // if the modificaton bit of victim = 1, write back
                    write++;
                    interrupt++;  
                }
                frame.push(reference);
                pageInMem.insert(reference);
            }
            modificationBits[reference] = modification;
        }
        //case 2: find page in mem
        else if (modificationBits[reference] == 0 && modification == 1) {  // renew modification bit
            modificationBits[reference] = 1;
        }
    }
}


// Optimal 
void optimal(int frameCount, const vector<vector<int>>& pages, int& pageFault, int& interrupt, int& write) {
    pageFault = 0;
    interrupt = 0;
    write = 0;

    vector<int> frame;
    unordered_map<int, int> modificationBits;

    for (int i = 0; i < pages.size(); i++) {
        int reference = pages[i][0];
        int modification = pages[i][1];
        //case 1: cant find page in mem, page fault
        if (find(frame.begin(), frame.end(), reference) == frame.end()) {  
            pageFault++;
            interrupt++;
            if (frame.size() < frameCount) {  // case 1-1 if mem is not full
                frame.push_back(reference);
                modificationBits[reference] = modification;
            }
            else {  // case1-2 mem is full, page replacement is needed
                int victimPointer = -1;
                int maxDistance = -1;

                // find the page wont be used in the future
                for (int j = 0; j < frame.size(); j++) {
                    int pointer = i + 1;
                    //if pages[pointer][0] == frame[j], means this page will be used soon
                    while (pointer < pages.size() && pages[pointer][0] != frame[j]) {
                        pointer++;
                    }
                    // this page wont be used in the future, it can be the victim
                    if (pointer >= pages.size()) {  
                        victimPointer = j;
                        break;
                    }
                    //this page will be the farest page, it can be the victim
                    if (pointer - i > maxDistance) {
                        maxDistance = pointer - i;
                        victimPointer = j;
                    }
                }
                int victim = frame[victimPointer];
                if (modificationBits[victim] == 1) {  // if the modificaton bit of victim = 1 write back
                    write++;
                    interrupt++;  
                }
                frame[victimPointer] = reference;
                modificationBits.erase(victim);
                modificationBits[reference] = modification;
            }         
        } //case 2: find page in mem
        else if (modificationBits[reference] == 0 && modification == 1) { // renew modification bit
            modificationBits[reference] = 1;
        }
    }
}
//enhanced second chance algo, search (reference bit, modification bit)=(0,0)
int searchZeroZero(deque<int>&frame, unordered_map<int, pair<int, int>>&pageBits, int& pointer) {
    int startPointer = pointer;
    do {
        int pageNum = frame[pointer];
        if (pageBits[pageNum].first == 0 && pageBits[pageNum].second == 0) {
            return pointer;
        }//reset reference bit 1 -> 0
        else if (pageBits[pageNum].first == 1) {
            pageBits[pageNum].first = 0;
        }
        pointer = (pointer + 1) % frame.size();  //like circular queue
    } while (pointer != startPointer);
    return -1; // can't find(0,0)
}
// search (reference bit, modification bit)=(0,1)
int searchZeroOne(deque<int>&frame, unordered_map<int, pair<int, int>>&pageBits, int& pointer) {
    int startPointer = pointer;
    do {
        int pageNum = frame[pointer];
        if (pageBits[pageNum].first == 0 && pageBits[pageNum].second == 1) {
            return pointer;
        }
        pointer = (pointer + 1) % frame.size();
    } while (pointer != startPointer);
    return -1;  // can't find(0,1)
}
void enhancedSecondChance(int frameCount, const vector<vector<int>>& pages, int& pageFault, int& interrupt, int& write) {
    pageFault = 0;
    interrupt = 0;
    write = 0;

    deque<int> frame;  
    unordered_set<int> pageInMem;
    unordered_map<int, pair<int, int>> pageBits;  // {pageNum: {referenceBit, modificationBit}}

    for (const auto& page : pages) {
        int reference = page[0];
        int modification = page[1];

        if (pageInMem.find(reference) == pageInMem.end()) { 
            pageFault++;
            interrupt++;
            if (frame.size() < frameCount) {  
                frame.push_back(reference);
                pageInMem.insert(reference);
            }
            else {
                int victimIndex = -1;
                int pointer = 0;
                // 4 round to check
                for (int round = 1; round <= 4; round++) {
                    if (round == 1 || round == 3) {
                        victimIndex = searchZeroZero(frame, pageBits, pointer);
                    }
                    else if (round == 2 || round == 4) {
                        victimIndex = searchZeroOne(frame, pageBits, pointer);
                    }
                    if (victimIndex != -1) {   //find victim
                        break;  
                    }
                }       
                int victim = frame[victimIndex];
                pageInMem.erase(victim);  
                //if modificatio bit of victim = 1, write back
                if (pageBits[victim].second == 1) { 
                    write++;
                    interrupt++;  
                }
                frame[victimIndex] = reference;  
                pageInMem.insert(reference); 
                pageBits.erase(victim); 
            }
            // renew new page
            pageBits[reference] = { 1, modification };  
        }
        else if (pageBits[reference].first == 0 || (pageBits[reference].second == 0 && modification == 1)) {
            pageBits[reference] = { 1, modification };
        }
    }
}

void myAlgo(int frameCount, const vector<vector<int>>& pages, int& pageFault, int& interrupt, int& write) {
    pageFault = 0;
    interrupt = 0;
    write = 0;

    deque<int> frame;  
    unordered_set<int> pageInMem;  
    unordered_map<int, int> modificationBits; 
    unordered_map<int, int> useCountBits;  // Count the number of times the page has been used

    deque<int> zone1, zone2;  // divide whole frame into 3 part, set their size
    int zone1MaxSize = frameCount / 2;  
    int zone2MaxSize = frameCount / 2;  
    int upgradeThreshold = 2; // the page need to be access >= 2 times, then it can be moved to zone1

    for (const auto& page : pages) {
        int reference = page[0];  
        int modification = page[1];

        //case 1: cant find page in mem, page fault
        if (pageInMem.find(reference) == pageInMem.end()) {
            pageFault++;
            interrupt++;
            if (frame.size() < frameCount) { // case 1-1 if mem is not full
                frame.push_back(reference);
                pageInMem.insert(reference);
                if (zone2.size() < zone2MaxSize) {
                    zone2.push_back(reference);  // put new page into zone2 first
                }
                else {
                    // if zone2 is full, use FIFO remove victim
                    int victim = zone2.front();
                    zone2.pop_front();
                    pageInMem.erase(victim);
                    if (modificationBits[victim] == 1) {
                        write++;
                        interrupt++;
                    }
                    frame.erase(remove(frame.begin(), frame.end(), victim), frame.end());
                    zone2.push_back(reference);
                }
                useCountBits[reference] = 1;
                modificationBits[reference] = modification;
            }
            else {  // case 1-2: mem is full, page replacement
                int victim = -1;

                // choose victim from zone2 
                if (!zone2.empty()) {
                    victim = zone2.front();
                    zone2.pop_front();
                }
                frame.pop_front();
                pageInMem.erase(victim);

                if (modificationBits[victim] == 1) {
                    write++;
                    interrupt++;
                }
                modificationBits.erase(victim);
                useCountBits.erase(victim);

                // put new page into zone2
                frame.push_back(reference);
                pageInMem.insert(reference);
                zone2.push_back(reference);  
                useCountBits[reference] = 1;
                modificationBits[reference] = modification;
            }
        }
        else {  //case 2: find page in mem
            // increase page access number
            useCountBits[reference]++;

            // if count > thershold, move it into zone1
            if (useCountBits[reference] >= upgradeThreshold) {
                // check whether page is in zone1
                if (find(zone1.begin(), zone1.end(), reference) == zone1.end()) {
                    // if zone1 is full, move first page to zone2
                    if (zone1.size() >= zone1MaxSize) {
                        int zone1Victim = zone1.front();
                        zone1.pop_front();

                        // if zone1 + zone2 are full, move first page in zone2
                        if (zone2.size() >= zone2MaxSize) {                           
                            int zone2Victim = zone2.front();
                            zone2.pop_front();
                            pageInMem.erase(zone2Victim);  
                        }
                       //move zone1Victim to zone2
                        zone2.push_back(zone1Victim);
                    }
                   
                    zone2.erase(remove(zone2.begin(), zone2.end(), reference), zone2.end());
                    zone1.push_back(reference);  
                }
            }
            // renew modification bit
            if (modificationBits[reference] == 0 && modification == 1) {
                modificationBits[reference] = 1;
            }
        }
    }
}

// generate random reference string
vector<vector<int>> randomReferenceString(int memRef_num) {
    vector<vector<int>> refString; //{pageNum, modificationBit}
    refString.reserve(memRef_num);

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> pageDist(1, 1200);
    uniform_int_distribution<> modificationDist(0, 1);

    for (int i = 0; i < memRef_num; i++) {
        int pageNum = pageDist(gen);
        int modification = modificationDist(gen);
        refString.push_back({ pageNum, modification });
    }
    return refString;
}

// generate locality reference string
vector<vector<int>> localityReferenceString(int memRef_num) {
    vector<vector<int>> refString;
    refString.reserve(memRef_num); 

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> pageDist(1, 1200);  
    uniform_int_distribution<> modificationDist(0, 1); 
    uniform_int_distribution<> lengthDist(memRef_num / 200, memRef_num / 100); 

    int remainingRef = memRef_num;  // to make sure sum of length which generate each time <= memRef_num

    while (remainingRef > 0) {
        // generate lengthDist randomly
        int procedureLength = min(lengthDist(gen), remainingRef);  // must <= remaining length
        int basePage = pageDist(gen);  //pick a basepage random

        for (int j = 0; j < procedureLength; j++) {
            int pageNum = basePage + j % 50;  // limit access to 50 pages near basepage
            int modification = modificationDist(gen);  
            refString.push_back({ pageNum, modification });
        }
        remainingRef -= procedureLength; 
    }
    return refString;
}
//generate my reference string
vector<vector<int>> myReferenceString(int memRef_num) {
    vector<vector<int>> refString;
    refString.reserve(memRef_num);
    random_device rd;
    mt19937 gen(rd());
    // Set the range of high-frequency and low-frequency pages
    uniform_int_distribution<> highFreqPageDist(1, 100);  
    uniform_int_distribution<> lowFreqPageDist(101, 1200);  
    uniform_int_distribution<> modificationDist(0, 1);  

    int remainingRef = memRef_num;

    // 60% visits on high frequency pages, 40% on low frequency pages
    int highFreqRef = remainingRef * 0.6; 
    int lowFreqRef = remainingRef * 0.4;   
    // generate high freq ref string
    for (int i = 0; i < highFreqRef; ++i) {
        int pageNum = highFreqPageDist(gen);  // high frequency pages
        int modification = modificationDist(gen);
        refString.push_back({ pageNum, modification });
    }
    // generate low freq ref string
    for (int i = 0; i < lowFreqRef; ++i) {
        int pageNum = lowFreqPageDist(gen);  // low frequency pages
        int modification = modificationDist(gen);
        refString.push_back({ pageNum, modification });
    }  
    shuffle(refString.begin(), refString.end(), gen);
    return refString;
}


