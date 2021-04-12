//Sample read RGB values for SSTV
//
#include "stdint.h"
#include <iostream>
#include <fstream>

using namespace std;
uint32_t r,g,b;
int h;
int main(){
	fstream fred, fblue,fgreen;
	int c=0;
	fred.open("red.bin", ios::in);
	fgreen.open("green.bin", ios::in);
	fblue.open("blue.bin", ios::in);
	//This next part probably goes in the if code== MARTIN1 part 
	for(c = 0; c < 256; c++) {
		//Read in the red values
		for (int h=0; h < 320; h++){
			fred.read(reinterpret_cast<char *>(&r), sizeof(r));
			//ToneWait(r,456);
			cout << r;
		}
		cout << "Red done" << endl;

		for (int h=0; h < 320; h++){
			fgreen.read(reinterpret_cast<char *>(&g), sizeof(g));
			cout << g;
		}
		cout << "Green done\r" << endl;
		for (int h=0; h < 320; h++){
			fblue.read(reinterpret_cast<char *>(&b), sizeof(b));
			cout << b;
		}
		cout << "Blue done\r" << endl;
	}
cout << "Complete\r\n" << endl;
}
