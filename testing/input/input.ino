#include "LedControl.h"

int VRx = A0;
int VRy = A1;

int CLK = 8;
int CS = 9;
int DIN = 10;

int devices = 4;

int xPos = 0;
int yPos = 0;
LedControl LC = LedControl(DIN, CLK, CS, devices);

void setup()
{
  Serial.begin(9600);

  pinMode(VRx, INPUT);
  pinMode(VRy, INPUT);

  for (int address = 0; address < devices; address++)
  {
    LC.shutdown(address, false);
    LC.setIntensity(address, 1);
    LC.clearDisplay(address);
  }

  LC.setLed(0, xPos, yPos, true);
}

void loop()
{

  int mapX = analogRead(VRx);
  int mapY = analogRead(VRy);

  if (mapX > 750 && xPos < 7)
  {
    LC.setLed(0, xPos, yPos, false);
    xPos++;
    LC.setLed(0, xPos, yPos, true);
  }
  else if (mapX < 250 && xPos > 0)
  {
    LC.setLed(0, xPos, yPos, false);
    xPos--;
    LC.setLed(0, xPos, yPos, true);
  }

  if (mapY > 750 && yPos > 0)
  {
    LC.setLed(0, xPos, yPos, false);
    yPos--;
    LC.setLed(0, xPos, yPos, true);
  }
  else if (mapY < 250 && yPos < 7)
  {
    LC.setLed(0, xPos, yPos, false);
    yPos++;
    LC.setLed(0, xPos, yPos, true);
  }
  delay(100);
}
