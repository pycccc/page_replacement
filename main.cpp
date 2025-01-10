#include "pageReplacement.h"
#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> frameSizes = { 10, 20, 30, 40, 50, 60, 70, 80, 90, 100 };

    for (int frameCount : frameSizes) {
        cout << "���ծج[�ƶq: " << frameCount << endl;

        int pageFault, interrupt, write;

        // test on random reference string
        vector<vector<int>> randomPages = randomReferenceString(120000);
        fifo(frameCount, randomPages, pageFault, interrupt, write);
        cout << "�H���ѦҦr�ꪺ FIFO ���G:" << endl;
        cout << "PageFault: " << pageFault << " ; Interrupt: " << interrupt << " ; Write: " << write << endl;
        optimal(frameCount, randomPages, pageFault, interrupt, write);
        cout << "�H���ѦҦr�ꪺ Optimal ���G:" << endl;
        cout << "PageFault: " << pageFault << " ; Interrupt: " << interrupt << " ; Write: " << write << endl;
        enhancedSecondChance(frameCount, randomPages, pageFault, interrupt, write);
        cout << "�H���ѦҦr�ꪺ Enhanced Second Chance ���G:" << endl;
        cout << "PageFault: " << pageFault << " ; Interrupt: " << interrupt << " ; Write: " << write << endl;
        myAlgo(frameCount, randomPages, pageFault, interrupt, write);
        cout << "�H���ѦҦr�ꪺ myAlgo ���G:" << endl;
        cout << "PageFault: " << pageFault << " ; Interrupt: " << interrupt << " ; Write: " << write << endl;
       
        cout << "===================================" << endl;

        // test on locality reference string
        vector<vector<int>> localityPages = localityReferenceString(120000);
        fifo(frameCount, localityPages, pageFault, interrupt, write);
        cout << "�ϰ�ʰѦҦr�ꪺ FIFO ���G:" << endl;
        cout << "PageFault: " << pageFault << " ; Interrupt: " << interrupt << " ; Write: " << write << endl;
        optimal(frameCount, localityPages, pageFault, interrupt, write);
        cout << "�ϰ�ʰѦҦr�ꪺ Optimal ���G:" << endl;
        cout << "PageFault: " << pageFault << " ; Interrupt: " << interrupt << " ; Write: " << write << endl;
        enhancedSecondChance(frameCount, localityPages, pageFault, interrupt, write);  
        cout << "�ϰ�ʰѦҦr�ꪺ Enhanced Second Chance ���G:" << endl;
        cout << "PageFault: " << pageFault << " ; Interrupt: " << interrupt << " ; Write: " << write << endl;
        myAlgo(frameCount, localityPages, pageFault, interrupt, write);
        cout << "�ϰ�ѦҦr�ꪺ myAlgo ���G:" << endl;
        cout << "PageFault: " << pageFault << " ; Interrupt: " << interrupt << " ; Write: " << write << endl;
        cout << "===================================" << endl;

        // test on my reference string
        vector<vector<int>> customPages = myReferenceString(60000);
        fifo(frameCount, customPages, pageFault, interrupt, write);
        cout << "�ۭq�ѦҦr�ꪺ FIFO ���G:" << endl;
        cout << "PageFault: " << pageFault << " ; Interrupt: " << interrupt << " ; Write: " << write << endl;
        optimal(frameCount, customPages, pageFault, interrupt, write);  
        cout << "�ۭq�ѦҦr�ꪺ Optimal ���G:" << endl;
        cout << "PageFault: " << pageFault << " ; Interrupt: " << interrupt << " ; Write: " << write << endl;
        enhancedSecondChance(frameCount, customPages, pageFault, interrupt, write); 
        cout << "�ۭq�ѦҦr�ꪺ Enhanced Second Chance ���G:" << endl;
        cout << "PageFault: " << pageFault << " ; Interrupt: " << interrupt << " ; Write: " << write << endl;
        myAlgo(frameCount, customPages, pageFault, interrupt, write);
        cout << "�ۭq�ѦҦr�ꪺ myAlgo ���G:" << endl;
        cout << "PageFault: " << pageFault << " ; Interrupt: " << interrupt << " ; Write: " << write << endl;
     
        cout << "-----------------------------" << endl;
    }

    return 0;
}
