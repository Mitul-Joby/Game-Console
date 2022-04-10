#include "LedControl.h"

int CLK = 8;
int CS = 9;
int DIN = 10;
int devices = 4;

LedControl LC = LedControl(DIN, CLK, CS, devices);

void setup()
{
  for (int address = 0; address < devices; address++)
  {
    LC.shutdown(address, false);
    LC.setIntensity(address, 1);
    LC.clearDisplay(address);
  }
}

void loop()
{
  for (int address = 0; address < devices; address++)
  {
    for (int y = 7; y >= 0; y--)
    {
      for (int x = 7; x >= 0; x--)
      {
        LC.setLed(address, x, y, true);
        delay(50);
      }
    }
  }

  for (int address = 0; address < devices; address++)
  {
    for (int y = 7; y >= 0; y--)
    {
      for (int x = 7; x >= 0; x--)
      {
        LC.setLed(address, x, y, false);
        delay(50);
      }
    }
  }
}
