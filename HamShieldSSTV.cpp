//Taken from Hamshield.cpp - only relavent portions.
// Goal: read csv for frequency values and iterate for each color/row/line. 
#include "HamShield.h"
#include "stdint.h"
#include <iostream>
#include <fstream>


void HamShield::SSTVVISCode(int code) { 
    toneWait(1900,300);
    toneWait(1200,10);
    toneWait(1900,300);
    toneWait(1200,30);
        for(int x = 0; x < 7; x++) { 
           if(code&(1<<x)) { toneWait(1100,30); } else { toneWait(1300,30); } 
        } 
        if(parityCalc(code)) { toneWait(1300,30); } else { toneWait(1100,30); } 
        toneWait(1200,30);
        return;
}

/* 

SSTV Test Pattern 
Print 6 color bars
MARTIN1 is only supported for this
Reference: http://www.barberdsp.com/files/Dayton%20Paper.pdf

*/

//void HamShield::SSTVTestPattern(int code) { 
int main() {
	uint32_t r,g,b;
	int code = 0;
	HamShield hs;
	hs.SSTVVISCode(code);
       std::fstream fred, fblue, fgreen;
       fred.open("red.bin", std::ios::in);
       fgreen.open("green.bin", std::ios::in);
       fblue.open("blue.bin", std::ios::in);
       if(code == MARTIN1) { 
            for(int x = 0; x < 256; x++){ 

		hs.toneWaitU(1200,4862);              // sync pulse (4862 uS)
                hs.toneWaitU(1500,572);               // sync porch (572 uS)

                for(int y = 0; y < 320; y++){
		fgreen.read(reinterpret_cast<char *>(&g), sizeof(g));
                hs.toneWait(g,456);
              }

                hs.toneWaitU(1500,572);               // color separator pulse (572 uS)

                //Blue Channel - 146.432ms a line (we are doing 144ms) 

                for(int z = 0; z< 320; z++){
                 hs.toneWait(b,456);
		fblue.read(reinterpret_cast<char *>(&b), sizeof(b));
              }

                 hs.toneWaitU(1500,572);               // color separator pulse (572 uS)

                //Red Channel - 146.432ms a line (we are doing 144ms)

               for(int w = 0; w < 320; w++){
		fred.read(reinterpret_cast<char *>(&g), sizeof(g));
                 hs.toneWait(r,456);
              }

                hs.toneWaitU(1500,572);               // color separator pulse (572 uS)
                
            }

       } 
}
/* wait for tone to complete */

void HamShield::toneWait(uint16_t freq, long timer) { 
    HStone(hs_mic_pin,freq);//,timer);
    HSdelay(timer);
    HSnoTone(hs_mic_pin);
}

/* wait microseconds for tone to complete */

void HamShield::toneWaitU(uint16_t freq, long timer) { 
    if(freq < 16383) { 
    HStone(hs_mic_pin,freq);
    HSdelayMicroseconds(timer); HSnoTone(hs_mic_pin); return;
    }
    HStone(hs_mic_pin,freq);
    HSdelay(timer / 1000); HSnoTone(hs_mic_pin); return;
}


bool HamShield::parityCalc(int code) {  
     unsigned int v;       // word value to compute the parity of
     bool parity = false;  // parity will be the parity of v

    while (code)
    {
       parity = !parity;
       code = code & (code - 1);
    }

    return parity;
}

