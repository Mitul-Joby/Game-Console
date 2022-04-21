#include "time.h"
#include "LedControl.h"

int VRx = A0;
int VRy = A1;

// int SW = 2;
int CLK = 8;
int CS = 9;
int DIN = 10;

int devices = 4;

LedControl LC = LedControl(DIN, CLK, CS, devices);

int matrix[8][32] = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};


void displayMatrix()
{

  // Set Row
  for (int y = 0; y < 8; y++)
  {
    int disp = 3, sum = 0, onOff;
    int bin = 7;
    for (int x = 31; x >= 0; x--)
    {
      sum = sum << 1;
      onOff = (matrix[7 - y][x]) ? 1 : 0;
      sum = sum ^ onOff;
      bin--;
      if (bin == -1)
      {
        LC.setRow(disp, y, sum);
        sum = 0;
        bin = 7;
        disp--;
      }
    }
  }
}

void initDisplay()
{
  for (int address = 0; address < devices; address++)
  {
    LC.shutdown(address, false);
    LC.setIntensity(address, 1);
    LC.clearDisplay(address);
  }
}



void serialDisplay()
{
  int i, j;
  for (i = 0; i < 8; i++)
  {
    for (j = 0; j < 32; j++)
    {
      Serial.print(matrix[i][j]);
      if (matrix[i][j] > 1)
        matrix[i][j] = 0;
    }
    Serial.print("\n");
  }
}



enum DIRECTION
{
  UP,
  DOWN,
  LEFT,
  RIGHT
};

struct AsteroidGameConfig{
  int lives;
  int score;
} asteroidGame;

struct AsteroidShip
{
  int y;
} asteroidShip;

void initAsteroidLives(int lives)
{
  asteroidGame.lives = lives;
}

void initAsteroidGame()
{
  asteroidShip.y = 3;
}

void updateAsteroidGame()
{
  matrix[asteroidShip.y - 1] [0]= 1;
  matrix[asteroidShip.y]     [0]= 1;    
  matrix[asteroidShip.y]     [1]= 1;    
  matrix[asteroidShip.y + 1] [0]= 1;  
}

void asteroidGameLoop()
{
  updateAsteroidGame();
  displayMatrix();

  int X = analogRead(VRx);
  if (X > 256)
  {
    asteroidShip.y++;
  }
  if (X < 768)
  {
    asteroidShip.y--;
  }


  delay(100);
}

void setup()
{
  Serial.begin(9600);
  pinMode(VRx, INPUT);
  pinMode(VRy, INPUT);
  // pinMode(SW, INPUT_PULLUP);

  initDisplay();

  randomSeed(analogRead(0));
}

void loop()
{
  initAsteroidLives(3);
  initAsteroidGame();
  while(1)
  {
    asteroidGameLoop();
  }

}
