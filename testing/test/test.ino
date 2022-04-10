#include "LedControl.h"

LedControl LC=LedControl(10,8,9,4);

unsigned long delaytime=500;

void setup() {
  int devices=LC.getDeviceCount();
  for(int address=0;address<devices;address++) {
    LC.shutdown(address,false);
    LC.setIntensity(address,1);
    LC.clearDisplay(address);
  }
}

void loop() { 
  for (int addr = 0; addr < 4; addr++) {
   for (int y = 7; y >= 0; y--) {
     for (int x = 7; x >= 0; x--) {
        LC.setLed(addr, x, y, true);
        delay(50);
      }
    }
  }

  for (int addr = 0; addr < 4; addr++) {
   for (int y = 7; y >= 0; y--) {
     for (int x = 7; x >= 0; x--) {
        LC.setLed(addr, x, y, false);
        delay(50);
      }
    }
  }
}
