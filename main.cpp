#include "pageReplacement.h"
#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> frameSizes = { 10, 20, 30, 40, 50, 60, 70, 80, 90, 100 };

    for (int frameCount : frameSizes) {
        cout << "測試框架數量: " << frameCount << endl;

        int pageFault, interrupt, write;

        // test on random reference string
        vector<vector<int>> randomPages = randomReferenceString(120000);
        fifo(frameCount, randomPages, pageFault, interrupt, write);
        cout << "隨機參考字串的 FIFO 結果:" << endl;
        cout << "PageFault: " << pageFault << " ; Interrupt: " << interrupt << " ; Write: " << write << endl;
        optimal(frameCount, randomPages, pageFault, interrupt, write);
        cout << "隨機參考字串的 Optimal 結果:" << endl;
        cout << "PageFault: " << pageFault << " ; Interrupt: " << interrupt << " ; Write: " << write << endl;
        enhancedSecondChance(frameCount, randomPages, pageFault, interrupt, write);
        cout << "隨機參考字串的 Enhanced Second Chance 結果:" << endl;
        cout << "PageFault: " << pageFault << " ; Interrupt: " << interrupt << " ; Write: " << write << endl;
        myAlgo(frameCount, randomPages, pageFault, interrupt, write);
        cout << "隨機參考字串的 myAlgo 結果:" << endl;
        cout << "PageFault: " << pageFault << " ; Interrupt: " << interrupt << " ; Write: " << write << endl;
       
        cout << "===================================" << endl;

        // test on locality reference string
        vector<vector<int>> localityPages = localityReferenceString(120000);
        fifo(frameCount, localityPages, pageFault, interrupt, write);
        cout << "區域性參考字串的 FIFO 結果:" << endl;
        cout << "PageFault: " << pageFault << " ; Interrupt: " << interrupt << " ; Write: " << write << endl;
        optimal(frameCount, localityPages, pageFault, interrupt, write);
        cout << "區域性參考字串的 Optimal 結果:" << endl;
        cout << "PageFault: " << pageFault << " ; Interrupt: " << interrupt << " ; Write: " << write << endl;
        enhancedSecondChance(frameCount, localityPages, pageFault, interrupt, write);  
        cout << "區域性參考字串的 Enhanced Second Chance 結果:" << endl;
        cout << "PageFault: " << pageFault << " ; Interrupt: " << interrupt << " ; Write: " << write << endl;
        myAlgo(frameCount, localityPages, pageFault, interrupt, write);
        cout << "區域參考字串的 myAlgo 結果:" << endl;
        cout << "PageFault: " << pageFault << " ; Interrupt: " << interrupt << " ; Write: " << write << endl;
        cout << "===================================" << endl;

        // test on my reference string
        vector<vector<int>> customPages = myReferenceString(60000);
        fifo(frameCount, customPages, pageFault, interrupt, write);
        cout << "自訂參考字串的 FIFO 結果:" << endl;
        cout << "PageFault: " << pageFault << " ; Interrupt: " << interrupt << " ; Write: " << write << endl;
        optimal(frameCount, customPages, pageFault, interrupt, write);  
        cout << "自訂參考字串的 Optimal 結果:" << endl;
        cout << "PageFault: " << pageFault << " ; Interrupt: " << interrupt << " ; Write: " << write << endl;
        enhancedSecondChance(frameCount, customPages, pageFault, interrupt, write); 
        cout << "自訂參考字串的 Enhanced Second Chance 結果:" << endl;
        cout << "PageFault: " << pageFault << " ; Interrupt: " << interrupt << " ; Write: " << write << endl;
        myAlgo(frameCount, customPages, pageFault, interrupt, write);
        cout << "自訂參考字串的 myAlgo 結果:" << endl;
        cout << "PageFault: " << pageFault << " ; Interrupt: " << interrupt << " ; Write: " << write << endl;
     
        cout << "-----------------------------" << endl;
    }

    return 0;
}
