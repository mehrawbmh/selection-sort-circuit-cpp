#ifndef CA4_CONTROLLER_HPP
#define CA4_CONTROLLER_HPP

#include "classVectorPrimitives.h"

class Controller {
private:
    bool shouldSwap = false;
    bus *clk, *rst, *cnt1Load, *cnt2Load, *cnt1Enable, *cnt2Enable, *regWrEn, *start, *done,
            *regRdEn, *selMin, *selAdr, *ldMinVal, *ldMinAdr, *ldTmp, *lt, *count1, *count2;

    int pState, nState;

public:
    Controller(bus &clk_, bus &rst_, bus &cnt1Ld, bus&cnt2Ld, bus &cnt1En,
    bus &cnt2En, bus &selAdr_, bus &selMin_, bus &ldMinVal_, bus &ldMinAdr_, bus &done,
            bus &ldTmp_, bus &wrEn, bus &rdEn, bus &lt_, bus &count1_, bus &count2_, bus &start_):
    clk(&clk_), rst(&rst_), cnt1Load(&cnt1Ld), cnt2Load(&cnt2Ld),
    cnt1Enable(&cnt1En), cnt2Enable(&cnt2En), selAdr(&selAdr_), lt(&lt_),
    selMin(&selMin_), regRdEn(&rdEn), regWrEn(&wrEn), ldMinAdr(&ldMinAdr_), done(&done),
    ldTmp(&ldTmp_), ldMinVal(&ldMinVal_), count1(&count1_), count2(&count2_), start(&start_)
    {
        pState = 0;
        nState = 0;
    }

    void evl();
    void report() {
        cout << "*** controller report ***\n";
        cout << "present state: " << pState << endl;
        cout << "next state: " << nState << endl;
        cout << "start: " << *start << endl;
        cout << "counter 1, load and enable: " << *cnt1Load << " , " << *cnt1Enable << endl;
        cout << "counter 2, load and enable: " << *cnt2Load << " , " << *cnt2Enable << endl;
        cout << "register file: read and write enables: " << *regRdEn << " , " << *regWrEn << endl;
        cout << "MUX: selMin, selAdr: " << *selMin << " , " << *selAdr << endl;
        cout << "registers: loadMin, loadTmp, loadAdr: " << *ldMinVal << " , " << *ldTmp << " , " << *ldMinAdr << endl;
        cout << "counter 1 and counter 2 values: " << *count1 << " , " << *count2 << endl;
        cout << "LT signal: " << *lt << endl;
        cout << "DONE: " << *done << endl;
    }
};


#endif //CA4_CONTROLLER_HPP
