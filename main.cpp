#include <iostream>
#include "classVectorPrimitives.h"
#include "datapath.hpp"
#include "controller.hpp"

using namespace std;

int main() {
    cout << "program started." << endl;

    bus clk(1, 'P');
    bus rst("1");
    bus start("0");
    bus done;

    bus count1(9), count2(9);
    bus cnt1Ld("0"), cnt2Ld("0"), cnt1En("0"), cnt2En("0"), ldMinVal("0"), ldMinAdr("0"),
            rfRdEn("0"), rfWrEn("0"), ldTmp("0");
    bus selAdr(2, '0'), selMin(1, '0');
    bus lt;


    Datapath dp(
            clk, rst, cnt1Ld, cnt2Ld, cnt1En, cnt2En,
            selAdr, selMin, ldMinVal, ldMinAdr, ldTmp,
            rfWrEn, rfRdEn, lt, count1, count2
    );

    Controller ctr(
            clk, rst, cnt1Ld, cnt2Ld, cnt1En, cnt2En,
            selAdr, selMin, ldMinVal, ldMinAdr, done, ldTmp,
            rfWrEn, rfRdEn, lt, count1, count2, start
    );

    dp.evl();
    ctr.evl();
    rst.fill('0');
    dp.initRegisterFile();
    start.fill('1');

    while (done != "1") {
        dp.evl();
        ctr.evl();
        start.fill('0');
    }

    dp.dumpRegisterFile("sorted2.txt");


    cout << "program finished. " << endl;
    return 0;
}
