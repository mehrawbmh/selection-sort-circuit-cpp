#ifndef CA4_DATAPATH_HPP
#define CA4_DATAPATH_HPP

#include "classVectorPrimitives.h"

#define REG_FILE_SIZE 256

class Datapath {
private:
    bus *clk, *rst, *cnt1Load, *cnt2Load, *cnt1Enable, *cnt2Enable, *regWrEn,
            *regRdEn, *selMin, *selAdr, *ldMinVal, *ldMinAdr, *ldTmp, *lt, *count1, *count2;

    bus minAdr, minVal, readData, tempReg, tempRegIn, gt, eq, adrBus;
    Comparator cmp;
    Memory regFile;
    bus cn1LoadData = bus(9, '0');
    dRegisterRaE minAddress, minValue, tempRegister;
    upCounterRaE cnt1, cnt2;
    Mux selMinMux;
    Mux3 selAdrMux;

    void report() {
        cout << "$$$ DATAPATH report $$$" << endl;
        cout << "register file read data: " << readData << endl;
        cout << "register file address data: " << adrBus << endl;
        cout << "register file write data: " << tempReg << endl;
        cout << "min address reg output: " << minAdr << endl;
        cout << "min val reg output: " << minVal << endl;
        cout << "tempReg input: " << tempRegIn << endl;
        cout << "lt, eq, gt: " << *lt << eq << gt << endl;
        cout << "cnt1: " << *count1 << " | cnt2: " << *count2 << endl;
        cout << "$$$ end datapath report $$$" << endl << endl;
    }

public:
    Datapath(bus &clk_, bus &rst_, bus &cnt1Ld, bus &cnt2Ld, bus &cnt1En,
             bus &cnt2En, bus &selAdr_, bus &selMin_, bus &ldMinVal_, bus &ldMinAdr_,
             bus &ldTmp_, bus &wrEn, bus &rdEn, bus &lt_, bus &count1_, bus &count2_) :
            clk(&clk_), rst(&rst_), cnt1Load(&cnt1Ld), cnt2Load(&cnt2Ld),
            cnt1Enable(&cnt1En), cnt2Enable(&cnt2En), selAdr(&selAdr_), lt(&lt_),
            selMin(&selMin_), regRdEn(&rdEn), regWrEn(&wrEn), ldMinAdr(&ldMinAdr_),
            ldTmp(&ldTmp_), ldMinVal(&ldMinVal_), count1(&count1_), count2(&count2_),
            cmp(readData, minVal, *lt, eq, gt),
            regFile(*rst, *clk, *regRdEn, *regWrEn, tempReg, adrBus, readData, REG_FILE_SIZE),
            minAddress(*count2, *clk, *rst, *ldMinAdr, minAdr),
            minValue(readData, *clk, *rst, *ldMinVal, minVal),
            tempRegister(tempRegIn, *clk, *rst, *ldTmp, tempReg),
            selMinMux(readData, minVal, *selMin, tempRegIn),
            selAdrMux(*count1, *count2, minAdr, *selAdr, adrBus),
            cnt1(cn1LoadData, *clk, *rst, *cnt1Load, *cnt1Enable, *count1),
            cnt2(*count1, *clk, *rst, *cnt2Load, *cnt2Enable, *count2) {
        this->minAdr = bus(8);
        this->minVal = bus(16);
        this->readData = bus(16);
        this->tempRegIn = bus(16);
        this->tempReg = bus(16);
    }

    void dumpRegisterFile(const string &dumpFileName);

    void initRegisterFile();

    void evl();
};


#endif //CA4_DATAPATH_HPP
