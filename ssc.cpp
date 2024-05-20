#include "ssc.hpp"
#include "controller.hpp"
#include "datapath.hpp"

SSC::SSC(bus &clk_, bus &rst_, bus &start_, bus &done_): clk(&clk_), rst(&rst_), start(&start_), done(&done_)
{
    count1 = bus(REG_FILE_ADDR_SIZE+1);
    count2 = bus(REG_FILE_ADDR_SIZE+1);
    cnt1Ld = bus("0");
    cnt2Ld = bus("0");
    cnt1En = bus("0");
    cnt2En = bus("0");
    ldMinVal = bus("0");
    ldMinAdr = bus("0");
    ldTmp = bus("0");
    rfWrEn = bus("0");
    rfRdEn = bus("0");
    selMin = bus("0");
    selAdr = bus(2, '0');
}

void SSC::evl() {
    Datapath dp(
            *clk, *rst, cnt1Ld, cnt2Ld, cnt1En, cnt2En,
            selAdr, selMin, ldMinVal, ldMinAdr, ldTmp,
            rfWrEn, rfRdEn, lt, count1, count2
    );

    Controller ctr(
            *clk, *rst, cnt1Ld, cnt2Ld, cnt1En, cnt2En,
            selAdr, selMin, ldMinVal, ldMinAdr, *done, ldTmp,
            rfWrEn, rfRdEn, lt, count1, count2, *start
    );

    dp.evl();
    ctr.evl();
    rst->fill('0');
    dp.initRegisterFile();
    start->fill('1');

    while (*done != "1") {
        dp.evl();
        ctr.evl();
        start->fill('0');
    }

    dp.dumpRegisterFile("sorted_v1.txt");


    cout << "program finished. " << endl;
}
