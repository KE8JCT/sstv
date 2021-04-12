//Taken from Hamshield.cpp - only relavent portions.
// Goal: read csv for frequency values and iterate for each color/row/line. 
#include "HamShield.h"
#include "stdint.h"
#include <fstream>


/*
SSTV Test Pattern 
Print 6 color bars
MARTIN1 is only supported for this
Reference: http://www.barberdsp.com/files/Dayton%20Paper.pdf

*/
#define MIC_PIN 3
#define RESET_PIN A3
#define SWITCH_PIN 2

#define DOT 100
#define CALLSIGN "W2KGY"
HamShield hs;
int16_t rssi;
//void HamShield::SSTVTestPattern(int code) { 
int main
() {
	uint32_t r,g,b;
	int code = MARTIN1;
	hs.SSTVVISCode(code);
	hs.setModeTransmit();
	delay(250);
       std::fstream fred, fblue, fgreen;
       fred.open("red.bin", std::ios::in);
       fgreen.open("green.bin", std::ios::in);
       fblue.open("blue.bin", std::ios::in);
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

