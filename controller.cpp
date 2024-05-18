#include "controller.hpp"

void Controller::evl() {
    //set default values for outputs
    cnt1Load->fill('0');
    cnt2Load->fill('0');
    cnt1Enable->fill('0');
    cnt2Enable->fill('0');
    regWrEn->fill('0');
    regRdEn->fill('0');
    selMin->fill('x');
    selAdr->fill("xx");
    ldMinVal->fill('0');
    ldMinAdr->fill('0');
    ldTmp->fill('0');
    done->fill('0');

    switch (pState) {
        case 0: //IDLE
            nState = (start->ival() == 1) ? 1 : 0;
            break;
        case 1: //Reset
            nState = 2;
            break;
        case 2: //LoadCnt2
            nState = 3;
            break;
        case 3: { //init Regs
            shouldSwap = false;
            nState = 4;
            break;
        }
        case 4: //inner loop
            nState = count2->at(8) == "0" ? 5 : shouldSwap ? 7 : 10;
            break;
        case 5: //compare
            nState = lt->at(0) == "1" ? 6 : 4;
            break;
        case 6: { //update MinVal and MinAdr
            nState = 4;
            shouldSwap = true;
            break;
        }
        case 7: //swap 1
            nState = 8;
            break;
        case 8: //swap 2
            nState = 9;
            break;
        case 9: //swap 3
            nState = 10;
            break;
        case 10: //outer loop
            nState = count1->at(8) == "0" ? 2 : 11;
            break;
        case 11: //DONE
            nState = 0;
            break;
        default:
            nState = 0;
    }

    switch (pState) {
        case 0: //IDLE
            break;
        case 1: //Reset
//            rst->fill('1');
            break;
        case 2: { //LoadCnt2
            cnt2Load->fill('1');
            cnt2Enable->fill('1');
            regRdEn->fill('1');
            selAdr->fill("00");
            break;
        }
        case 3: { //init Regs
            if (count1->ival() > 255) break;
            ldMinVal->fill('1');
            ldMinAdr->fill('1');
            ldTmp->fill('1');
            selMin->fill('0');
            break;
        }
        case 4: { //inner loop
//            selMin->fill('0'); //todo: one or zero?
            if (count1->ival() > 255) break;
            cnt2Enable->fill('1');
            selAdr->fill("01");
            regRdEn->fill('1');
            break;
        }
        case 5: { //compare
            selAdr->fill("01");  //todo
            if (count1->ival() > 255) break;
//            regRdEn->fill('1'); //todo
            break;
        }
        case 6: { //update MinVal and MinAdr
            ldMinAdr->fill('1');
            ldMinVal->fill('1');
            break;
        }
        case 7: //swap1: write bigger value to current addr from counter2
            selAdr->fill("10");
            regWrEn->fill('1');
//            ldMinVal->fill('1');
            break;
        case 8: { //swap2:
            selMin->fill('1');
            ldTmp->fill('1');
            selAdr->fill("00");
            break;
        }
        case 9: { //swap3: write samller value to current addr from counter1
            selAdr->fill("00");
            regWrEn->fill('1');
            break;
        }
        case 10: //outer loop
            cnt1Enable->fill('1');
            break;
        case 11: //DONE
            done->fill('1');
            break;
        default:
            cout << "******* HERE AT DEFAULT **********" << endl;
            break;
    }

    //todo: merge 2,3 and 8,9 states if possible?
//    this->report();
    cout << pState  << " : " << nState << '\t';
    pState = (rst->ival() == 1) ? 0 : (*clk == "P") ? nState: pState;

}
