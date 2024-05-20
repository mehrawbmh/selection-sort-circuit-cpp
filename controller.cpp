#include "controller.hpp"
#include "datapath.hpp"

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
            nState = count2->ival() < (REG_FILE_WORDS - 1) ? 5 : shouldSwap ? 7 : 9;
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
        case 9: //outer loop
            nState = count1->ival() < REG_FILE_WORDS ? 2 : 10;
            break;
        case 10: //DONE
            nState = 0;
            break;
        default:
            nState = 0;
    }

    switch (pState) {
        case 0: //IDLE
        case 1: //Reset
            break;
        case 2: { //LoadCnt2
            cnt2Load->fill('1');
            cnt2Enable->fill('1');
            regRdEn->fill('1');
            selAdr->fill("00");
            break;
        }
        case 3: { //init Regs
            ldMinVal->fill('1');
            ldMinAdr->fill('1');
            ldTmp->fill('1');
            selMin->fill('0');
            break;
        }
        case 4: { //inner loop
            cnt2Enable->fill('1');
            selAdr->fill("01");
            regRdEn->fill('1');
            break;
        }
        case 5: { //compare
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
            break;
        case 8: { //swap2:
            selMin->fill('1');
            ldTmp->fill('1');
            selAdr->fill("00");
            regWrEn->fill('1');
            break;
        }
        case 9: //outer loop
            cnt1Enable->fill('1');
            break;
        case 10: //DONE
            done->fill('1');
            break;
        default:
            cout << "******* HERE AT DEFAULT **********" << endl;
            break;
    }

//    cout <<  "step " << count1->ival() << " " << *count1 << " " << pState << ":" << nState << endl;
    if (count1->ival() == 1 && count2->ival() < 3) {
        this->report();
    }
    pState = (rst->ival() == 1) ? 0 : (*clk == "P") ? nState: pState;

}
