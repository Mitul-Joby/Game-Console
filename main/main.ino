// Could not refractor due to time crunch

#include "LedControl.h"

int VRx = A0;
int VRy = A1;
int IO = 7;
int SIG = 6;

int SW = 2;
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

enum GAMES {
  SNAKE,
  BREAKOUT
};


struct Snake
{
  int x;
  int y;
  int length;
  int direction;
  int score;
  int lives;
} snake;

struct Apple
{
  int x;
  int y;
} apple;

enum DIRECTION
{
  UP,
  DOWN,
  LEFT,
  RIGHT
};

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

void displayLogo(int game)
{
  digitalWrite(IO, 0);
  delay(100);
  digitalWrite(IO, 1);
  delay(100);

  digitalWrite(IO, 0);
  delay(100);
  digitalWrite(IO, 1);
  delay(100);

  digitalWrite(IO, 0);
  delay(100);
  digitalWrite(IO, 1);
  switch (game)
  {
    case SNAKE:
      LC.setRow(0, 7, 0b00000000);  LC.setRow(1, 7, 0b00000000);  LC.setRow(2, 7, 0b00000000); LC.setRow(3, 7, 0b00000000);
      LC.setRow(0, 6, 0b10111110);  LC.setRow(1, 6, 0b11001000);  LC.setRow(2, 6, 0b10011011); LC.setRow(3, 6, 0b00111110);
      LC.setRow(0, 5, 0b10000110);  LC.setRow(1, 5, 0b01101001);  LC.setRow(2, 5, 0b11011010); LC.setRow(3, 5, 0b00000110);
      LC.setRow(0, 4, 0b10000110);  LC.setRow(1, 4, 0b01101011);  LC.setRow(2, 4, 0b01111010); LC.setRow(3, 4, 0b00000110);
      LC.setRow(0, 3, 0b10111110);  LC.setRow(1, 3, 0b11101111);  LC.setRow(2, 3, 0b00111011); LC.setRow(3, 3, 0b00011110);
      LC.setRow(0, 2, 0b10110000);  LC.setRow(1, 2, 0b11101110);  LC.setRow(2, 2, 0b01111011); LC.setRow(3, 2, 0b00000110);
      LC.setRow(0, 1, 0b10110000);  LC.setRow(1, 1, 0b01001100);  LC.setRow(2, 1, 0b11011010); LC.setRow(3, 1, 0b00000110);
      LC.setRow(0, 0, 0b10111110);  LC.setRow(1, 0, 0b01001000);  LC.setRow(2, 0, 0b11011010); LC.setRow(3, 0, 0b00111110);
      break;
    
    case BREAKOUT:
      LC.setRow(0, 7, 0b00000000);  LC.setRow(1, 7, 0b00000000);  LC.setRow(2, 7, 0b00000000); LC.setRow(3, 7, 0b00000000);
      LC.setRow(0, 6, 0b00000000);  LC.setRow(1, 6, 0b00000000);  LC.setRow(2, 6, 0b00000000); LC.setRow(3, 6, 0b00000000);
      LC.setRow(0, 5, 0b00110011);  LC.setRow(1, 5, 0b10010011);  LC.setRow(2, 5, 0b00110010); LC.setRow(3, 5, 0b11101001);
      LC.setRow(0, 4, 0b01010101);  LC.setRow(1, 4, 0b10101001);  LC.setRow(2, 4, 0b01001010); LC.setRow(3, 4, 0b01001001);
      LC.setRow(0, 3, 0b00110011);  LC.setRow(1, 3, 0b10111011);  LC.setRow(2, 3, 0b01001001); LC.setRow(3, 3, 0b01001001);
      LC.setRow(0, 2, 0b01010101);  LC.setRow(1, 2, 0b10101001);  LC.setRow(2, 2, 0b01001010); LC.setRow(3, 2, 0b01001001);
      LC.setRow(0, 1, 0b01010011);  LC.setRow(1, 1, 0b10101011);  LC.setRow(2, 1, 0b00110010); LC.setRow(3, 1, 0b01000110);
      LC.setRow(0, 0, 0b00000000);  LC.setRow(1, 0, 0b00000000);  LC.setRow(2, 0, 0b00000000); LC.setRow(3, 0, 0b00000000);
      break;
  }
}

void displayLives(int lives)
{
  digitalWrite(IO, 0);
  delay(100);
  digitalWrite(IO, 1);
  delay(100);

  digitalWrite(IO, 0);
  delay(100);
  digitalWrite(IO, 1);
  delay(100);

  LC.setRow(0, 7, 0b00000000);  LC.setRow(1, 7, 0b00000000);  LC.setRow(2, 7, 0b00000000);
  LC.setRow(0, 6, 0b01000010);  LC.setRow(1, 6, 0b11010001);  LC.setRow(2, 6, 0b01110011);
  LC.setRow(0, 5, 0b01000010);  LC.setRow(1, 5, 0b01010001);  LC.setRow(2, 5, 0b00001000);
  LC.setRow(0, 4, 0b01000010);  LC.setRow(1, 4, 0b01010001);  LC.setRow(2, 4, 0b00001000);
  LC.setRow(0, 3, 0b01000010);  LC.setRow(1, 3, 0b11010001);  LC.setRow(2, 3, 0b00110001);
  LC.setRow(0, 2, 0b01000010);  LC.setRow(1, 2, 0b01010001);  LC.setRow(2, 2, 0b01000000);
  LC.setRow(0, 1, 0b01000010);  LC.setRow(1, 1, 0b01001010);  LC.setRow(2, 1, 0b01000000);
  LC.setRow(0, 0, 0b01011110);  LC.setRow(1, 0, 0b11000100);  LC.setRow(2, 0, 0b00111011);

  switch (lives)
  {
  case 0:
    LC.setRow(3, 7, 0b00000000);
    LC.setRow(3, 6, 0b00110000);
    LC.setRow(3, 5, 0b01001000);
    LC.setRow(3, 4, 0b01001000);
    LC.setRow(3, 3, 0b01001011);
    LC.setRow(3, 2, 0b01001000);
    LC.setRow(3, 1, 0b01001000);
    LC.setRow(3, 0, 0b00110000);
    break;

  case 1:
    LC.setRow(3, 7, 0b00000000);
    LC.setRow(3, 6, 0b00110000);
    LC.setRow(3, 5, 0b00111000);
    LC.setRow(3, 4, 0b00110000);
    LC.setRow(3, 3, 0b00110011);
    LC.setRow(3, 2, 0b00110000);
    LC.setRow(3, 1, 0b00110000);
    LC.setRow(3, 0, 0b01111000);
    break;

  case 2:
    LC.setRow(3, 7, 0b00000000);
    LC.setRow(3, 6, 0b00110000);
    LC.setRow(3, 5, 0b01001000);
    LC.setRow(3, 4, 0b01000000);
    LC.setRow(3, 3, 0b00100011);
    LC.setRow(3, 2, 0b00010000);
    LC.setRow(3, 1, 0b00001000);
    LC.setRow(3, 0, 0b01111000);
    break;

  case 3:
    LC.setRow(3, 7, 0b00000000);
    LC.setRow(3, 6, 0b00111000);
    LC.setRow(3, 5, 0b01000000);
    LC.setRow(3, 4, 0b01000000);
    LC.setRow(3, 3, 0b00111011);
    LC.setRow(3, 2, 0b01000000);
    LC.setRow(3, 1, 0b01000000);
    LC.setRow(3, 0, 0b00111000);
    break;

  case 4:
    LC.setRow(3, 7, 0b00000000);
    LC.setRow(3, 6, 0b01001000);
    LC.setRow(3, 5, 0b01001000);
    LC.setRow(3, 4, 0b01001000);
    LC.setRow(3, 3, 0b01111011);
    LC.setRow(3, 2, 0b01000000);
    LC.setRow(3, 1, 0b01000000);
    LC.setRow(3, 0, 0b01000000);
    break;

  case 5:
    LC.setRow(3, 7, 0b00000000);
    LC.setRow(3, 6, 0b01111000);
    LC.setRow(3, 5, 0b00001000);
    LC.setRow(3, 4, 0b00001000);
    LC.setRow(3, 3, 0b00111011);
    LC.setRow(3, 2, 0b01000000);
    LC.setRow(3, 1, 0b01000000);
    LC.setRow(3, 0, 0b00111000);
    break;

  case 6:
    LC.setRow(3, 7, 0b00000000);
    LC.setRow(3, 6, 0b00110000);
    LC.setRow(3, 5, 0b01001000);
    LC.setRow(3, 4, 0b00001000);
    LC.setRow(3, 3, 0b00111011);
    LC.setRow(3, 2, 0b01001000);
    LC.setRow(3, 1, 0b01001000);
    LC.setRow(3, 0, 0b00110000);
    break;

  }
}

void displayScore(int score)
{
  digitalWrite(IO, 0);
  delay(100);
  digitalWrite(IO, 1);
  delay(100);

  LC.setRow(0, 7, 0b00000000);  LC.setRow(1, 7, 0b00000000);  LC.setRow(2, 7, 0b00000000);
  LC.setRow(0, 6, 0b11000110);  LC.setRow(1, 6, 0b10011000);  LC.setRow(2, 6, 0b01110011);
  LC.setRow(0, 5, 0b00101001);  LC.setRow(1, 5, 0b10100101);  LC.setRow(2, 5, 0b00010100);
  LC.setRow(0, 4, 0b00100010);  LC.setRow(1, 4, 0b10100100);  LC.setRow(2, 4, 0b01110100);
  LC.setRow(0, 3, 0b00100100);  LC.setRow(1, 3, 0b10100100);  LC.setRow(2, 3, 0b01110011);
  LC.setRow(0, 2, 0b00101001);  LC.setRow(1, 2, 0b10100101);  LC.setRow(2, 2, 0b00010100);
  LC.setRow(0, 1, 0b11000110);  LC.setRow(1, 1, 0b10011000);  LC.setRow(2, 1, 0b01110100);
  LC.setRow(0, 0, 0b00000000);  LC.setRow(1, 0, 0b00000000);  LC.setRow(2, 0, 0b00000000);

  int rev = 0;
  while (score > 0)
  { 
      rev <<= 1;
      if (score & 1 == 1) 
          rev ^= 1;
      score >>= 1;
  }

  LC.setRow(3, 7, 0b00000000);
  LC.setRow(3, 6, rev);
  LC.setRow(3, 5, 0b00000000);
  LC.setRow(3, 4, 0b01100000);
  LC.setRow(3, 3, 0b10010000);
  LC.setRow(3, 2, 0b01000000);
  LC.setRow(3, 1, 0b00100000);
  LC.setRow(3, 0, 0b11110000);
}


void displayGameOver()
{
  LC.setRow(0, 7, 0b00000000);  LC.setRow(1, 7, 0b00000000);  LC.setRow(2, 7, 0b00000000); LC.setRow(3, 7, 0b00000000);
  LC.setRow(0, 6, 0b00000000);  LC.setRow(1, 6, 0b00000000);  LC.setRow(2, 6, 0b00000000); LC.setRow(3, 6, 0b00000000);
  LC.setRow(0, 5, 0b01110111);  LC.setRow(1, 5, 0b11101001);  LC.setRow(2, 5, 0b10101110); LC.setRow(3, 5, 0b01101110);
  LC.setRow(0, 4, 0b01010001);  LC.setRow(1, 4, 0b00101111);  LC.setRow(2, 4, 0b10101010); LC.setRow(3, 4, 0b10100010);
  LC.setRow(0, 3, 0b01110101);  LC.setRow(1, 3, 0b11101011);  LC.setRow(2, 3, 0b10101010); LC.setRow(3, 3, 0b01101110);
  LC.setRow(0, 2, 0b01010101);  LC.setRow(1, 2, 0b00101001);  LC.setRow(2, 2, 0b10101010); LC.setRow(3, 2, 0b10100010);
  LC.setRow(0, 1, 0b01010111);  LC.setRow(1, 1, 0b11101001);  LC.setRow(2, 1, 0b01001110); LC.setRow(3, 1, 0b10101110);
  LC.setRow(0, 0, 0b00000000);  LC.setRow(1, 0, 0b00000000);  LC.setRow(2, 0, 0b00000000); LC.setRow(3, 0, 0b00000000);
}

void initSnakeLives(int lives)
{
  snake.lives = lives;
}

void initSnakeGame()
{
  snake.x = 15;
  snake.y = 3;
  snake.direction = -1;
  snake.length = 1;
  snake.score = 0;

  apple.x = 15;
  apple.y = 1;

  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 32; j++)
    {
      matrix[i][j] = 0;
    }
  }

  displayLives(snake.lives);
  delay(1000);
  while(!digitalRead(SIG));
 
}

void updateSnakePositions()
{
  matrix[snake.y][snake.x] = snake.length;
  matrix[apple.y][apple.x] = -1;
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

  // // Set Individual LED
  // for (int x = 0; x < 32; x++)
  // {
  //   int disp = x / 8;
  //   int newX = x % 8;
  //   for (int y = 0; y < 8; y++)
  //   {
  //     int onOff = (matrix[y][x]) ? 1 : 0;
  //     LC.setLed(disp, 7 - y, 7 - newX, onOff);
  //   }
  // }
}

void newApple()
{
  apple.x = random(32);
  apple.y = random(8);

  if (matrix[apple.y][apple.x] > 0)
  {
    newApple();
  }
}

void updateSnakeGame()
{
  int i, j;
  for (i = 0; i < 8; i++)
  {
    for (j = 0; j < 32; j++)
    {
      if (matrix[i][j] > 0)
        matrix[i][j]--;
    }
  }
}

void updateSnake(int snakeX, int snakeY)
{
  if (snakeX > 768 && snake.direction != DOWN)
  {
    snake.direction = UP;
  }
  else if (snakeX < 256 && snake.direction != UP)
  {
    snake.direction = DOWN;
  }
  else if (snakeY > 768 && snake.direction != RIGHT)
  {
    snake.direction = LEFT;
  }
  else if (snakeY < 256 && snake.direction != LEFT)
  {
    snake.direction = RIGHT;
  }

  switch (snake.direction)
  {
    case UP:
      snake.y++;
      break;

    case DOWN:
      snake.y--;
      break;

    case LEFT:
      snake.x--;
      break;

    case RIGHT:
      snake.x++;
      break;
  }

  if (snake.x < 0)
  {
    snake.x = 31;
  }
  else if (snake.x > 31)
  {
    snake.x = 0;
  }
  if (snake.y < 0)
  {
    snake.y = 7;
  }
  else if (snake.y > 7)
  {
    snake.y = 0;
  }
}

void checkSnake(int *gameOver)
{
  if (snake.x == apple.x && snake.y == apple.y)
  {
    digitalWrite(IO, 0);
    delay(50);
    digitalWrite(IO, 1);
    snake.length++;
    snake.score += 1;
    newApple();
  }
  else if (matrix[snake.y][snake.x] > 0)
  {
    displayScore(snake.score);
    delay(1000);
    while(!digitalRead(SIG));

    snake.lives--;
    digitalWrite(IO, 0);
    delay(200);
    digitalWrite(IO, 1);
    
    initSnakeGame();
    if (snake.lives == 0)
    {
      digitalWrite(IO, 0);
      delay(100);
      digitalWrite(IO, 1);
      delay(100);

      digitalWrite(IO, 0);
      delay(200);
      digitalWrite(IO, 1);
      delay(100);

      digitalWrite(IO, 0);
      delay(100);
      digitalWrite(IO, 1);
      *gameOver = 1;
    }
  }
}

void snakeGame()
{
  displayLogo(SNAKE); 

  delay(1000);
  while(!digitalRead(SIG));

  initSnakeLives(3);
  initSnakeGame();

  int gameOver = 0;
  while (!gameOver)
  {
    updateSnakePositions();
    displayMatrix();

    int snakeX = analogRead(VRx);
    int snakeY = analogRead(VRy);
    updateSnake(snakeX, snakeY);

    updateSnakeGame();
    checkSnake(&gameOver);
    delay(100);
  }

  displayGameOver();
  delay(2000);
  while(!digitalRead(SIG));

}

// --------------------------------------------------------- //

struct BreakoutGameConfig
{
  int lives;
  int score;
} breakoutGame;

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
  if (Y > 768 || breakoutBall.direction == LEFT)
  {
      breakoutBall.direction = LEFT;
    if (breakoutPaddle.x > 2)
    {
      breakoutPaddle.x--;
    }
  }
  if (Y < 256 || breakoutBall.direction == RIGHT)
  {
      breakoutBall.direction = RIGHT;
    if (breakoutPaddle.x < 29)
    {
      breakoutPaddle.x++;
    }
  }
}

void initBreakoutLives(int lives)
{
  breakoutGame.lives = lives;
  breakoutGame.score = 0;
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
    if (!(i % 2)){
      for (j = 0; j < 32; j++)
      {
        matrix[i][j] = 1;
      }
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

void breakoutGameLoop(int *gameOver)
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
    displayLives(breakoutGame.lives);
    delay(1000);
    while(!digitalRead(SIG));
    if (breakoutGame.lives == 0)
    {
      *gameOver = 1;
    }
    else
    {
      initBreakoutBall();
      initBreakoutPaddle();
    }
  }
  else
  {
    breakoutBall.x += breakoutBall.dx;
    breakoutBall.y += breakoutBall.dy;
  }

}

void BreakoutGame()
{
  displayLogo(BREAKOUT); 

  delay(1000);
  while(!digitalRead(SIG));

  initBreakoutLives(6);
  
  displayLives(breakoutGame.lives);
  delay(1000);
  while(!digitalRead(SIG));
  
  initBreakoutGame();

  int gameOver = 0;

  while (!gameOver)
  {
    breakoutGameLoop(&gameOver);
    delay(100);
  }

  displayGameOver();
  delay(2000);
  while(!digitalRead(SIG));
}

void setup()
{
  pinMode(IO, OUTPUT);
  pinMode(SIG, INPUT);
  
  pinMode(VRx, INPUT);
  pinMode(VRy, INPUT);
  pinMode(SW, INPUT_PULLUP);


  initDisplay();

  randomSeed(analogRead(0));
}

void loop()
{

  if (digitalRead(SW))
  {
    snakeGame();
  }
  else
  {
    BreakoutGame();
  }
}