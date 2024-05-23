#include "datapath.hpp"

void Datapath::evl() {
    cnt1.evl();
    minAddress.evl();
    cnt2.evl();
    selMinMux.evl();
    tempRegister.evl();
    selAdrMux.evl();
    regFile.evl();
    minValue.evl();
    cmp.evl();

//    this->report();
}

void Datapath::initRegisterFile() {
    this->regFile.init("mem.txt");
}

void Datapath::dumpRegisterFile(const string &dumpFileName) {
    cout << "dumping memory...\n";
    this->regFile.dump(dumpFileName);
}
