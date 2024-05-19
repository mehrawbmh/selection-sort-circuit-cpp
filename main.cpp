#include <iostream>
#include "classVectorPrimitives.h"
#include "ssc.hpp"

using namespace std;

int main() {
    cout << "program started." << endl;

    bus clk(1, 'P');
    bus rst("1");
    bus start("0");
    bus done;

    SSC ssc(clk, rst, start, done);
    ssc.evl();
    return 0;
}
