#ifndef CA4_SSC_HPP
#define CA4_SSC_HPP

#include "classVectorPrimitives.h"

class SSC { // Selection-sorter-circuit
private:
    bus *clk, *rst, *start, *done;
    bus count1, count2, cnt1Ld, cnt2Ld, cnt1En, cnt2En, ldMinVal, ldMinAdr, rfRdEn, rfWrEn, ldTmp, selAdr, selMin, lt;
public:
    SSC(bus& clk, bus& rst, bus& start, bus& done);
    void evl();
};


#endif //CA4_SSC_HPP
