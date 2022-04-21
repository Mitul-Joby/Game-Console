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

enum DIRECTION
{
  UP,
  DOWN,
  LEFT,
  RIGHT
};

struct BreakoutGame
{
  int lives;
  int score;
} breakoutGame = {3, 0};

struct BreakoutBall
{
  int x;
  int y;
  int dx;
  int dy;
  int direction;
} breakoutBall;

struct BreakoutPaddle
{
  int x;
  int y;
} breakoutPaddle;

void inputBreakout(int X, int Y)
{
  if (Y > 750 || breakoutBall.direction == LEFT)
  {
      breakoutBall.direction = LEFT;
    if (breakoutPaddle.x > 2)
    {
      breakoutPaddle.x--;
    }
  }
  if (Y < 250 || breakoutBall.direction == RIGHT)
  {
      breakoutBall.direction = RIGHT;
    if (breakoutPaddle.x < 29)
    {
      breakoutPaddle.x++;
    }
  }
}

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

void initBreakoutBall()
{
  breakoutBall.x = 15;
  breakoutBall.y = 6;
  breakoutBall.dx = 1;
  breakoutBall.dy = 1;
  breakoutBall.direction = RIGHT;
}

void initBreakoutPaddle()
{
  breakoutPaddle.x = 15;
  breakoutPaddle.y = 7;
}

void initBreakoutGame()
{
  initBreakoutBall();
  initBreakoutPaddle();
  int i, j;
  for (i = 0; i < 3; i++)
  {
    for (j = 0; j < 32; j++)
    {
      matrix[i][j] = 1;
    }
  }
}

void updateBreakoutGame()
{
  matrix[breakoutPaddle.y][breakoutPaddle.x - 2] = 2;
  matrix[breakoutPaddle.y][breakoutPaddle.x - 1] = 2;
  matrix[breakoutPaddle.y][breakoutPaddle.x] = 2;
  matrix[breakoutPaddle.y][breakoutPaddle.x + 1] = 2;
  matrix[breakoutPaddle.y][breakoutPaddle.x + 2] = 2;

  matrix[breakoutBall.y][breakoutBall.x] = 3;
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

void breakoutGameLoop()
{
  updateBreakoutGame();

  displayMatrix();

  int X = analogRead(VRx);
  int Y = analogRead(VRy);

  inputBreakout(X, Y);
  serialDisplay();

  if (breakoutBall.y > 0 && matrix[breakoutBall.y - 1][breakoutBall.x] == 1)
  {
    matrix[breakoutBall.y - 1][breakoutBall.x] = 0;
    breakoutGame.score++;

    breakoutBall.dy = -breakoutBall.dy;
  }

  if (breakoutBall.y + 1 == 7 && (breakoutBall.x >= breakoutPaddle.x - 2 && breakoutBall.x <= breakoutPaddle.x + 2))
  {
    breakoutBall.dy = -breakoutBall.dy;
    if (breakoutBall.x < breakoutPaddle.x - 1)
    {
      breakoutBall.dx = -1;
    }
    if (breakoutBall.x > breakoutPaddle.x + 1)
    {
      breakoutBall.dx = +1;
    }
  }

  if (breakoutBall.x + breakoutBall.dx < 0 || breakoutBall.x + breakoutBall.dx > 31)
  {
    breakoutBall.dx = -breakoutBall.dx;
  }

  if (breakoutBall.y + breakoutBall.dy < 0)
  {
    breakoutBall.dy = -breakoutBall.dy;
  }

  if (breakoutBall.y + breakoutBall.dy > 7)
  {
    breakoutGame.lives--;
    initBreakoutBall();
    initBreakoutPaddle();
  }
  else
  {
    breakoutBall.x += breakoutBall.dx;
    breakoutBall.y += breakoutBall.dy;
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

  initBreakoutGame();
  while (1)
  {
    breakoutGameLoop();
  }
}
