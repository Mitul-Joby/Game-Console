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

void displayLives(int lives)
{
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
    LC.setRow(3, 6, 0b01111000);
    LC.setRow(3, 5, 0b01001000);
    LC.setRow(3, 4, 0b01001000);
    LC.setRow(3, 3, 0b01001011);
    LC.setRow(3, 2, 0b01001000);
    LC.setRow(3, 1, 0b01001000);
    LC.setRow(3, 0, 0b01111000);
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

  }
}

void displayLogo()
{
  LC.setRow(0, 7, 0b00000000);  LC.setRow(1, 7, 0b00000000);  LC.setRow(2, 7, 0b00000000); LC.setRow(3, 7, 0b00000000);
  LC.setRow(0, 6, 0b10111110);  LC.setRow(1, 6, 0b11001000);  LC.setRow(2, 6, 0b10011011); LC.setRow(3, 6, 0b00111110);
  LC.setRow(0, 5, 0b10000110);  LC.setRow(1, 5, 0b01101001);  LC.setRow(2, 5, 0b11011010); LC.setRow(3, 5, 0b00000110);
  LC.setRow(0, 4, 0b10000110);  LC.setRow(1, 4, 0b01101011);  LC.setRow(2, 4, 0b01111010); LC.setRow(3, 4, 0b00000110);
  LC.setRow(0, 3, 0b10111110);  LC.setRow(1, 3, 0b11101111);  LC.setRow(2, 3, 0b00111011); LC.setRow(3, 3, 0b00011110);
  LC.setRow(0, 2, 0b10110000);  LC.setRow(1, 2, 0b11101110);  LC.setRow(2, 2, 0b01111011); LC.setRow(3, 2, 0b00000110);
  LC.setRow(0, 1, 0b10110000);  LC.setRow(1, 1, 0b01001100);  LC.setRow(2, 1, 0b11011010); LC.setRow(3, 1, 0b00000110);
  LC.setRow(0, 0, 0b10111110);  LC.setRow(1, 0, 0b01001000);  LC.setRow(2, 0, 0b11011010); LC.setRow(3, 0, 0b00111110);
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

void initDisplay()
{
  for (int address = 0; address < devices; address++)
  {
    LC.shutdown(address, false);
    LC.setIntensity(address, 1);
    LC.clearDisplay(address);
  }
}

void initSnakeLives(int lives)
{
  snake.lives = lives;
}

void initGame()
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
  delay(5000);
 
}

void updateSnakePositions()
{
  matrix[snake.y][snake.x] = snake.length;
  matrix[apple.y][apple.x] = -1;
}

void displayMatrix()
{
  // Set Row 

  // for (int y = 0; y < 8; y++)
  // {
  //   int disp = 3, sum = 0, onOff;
  //   int bin = 7;
  //   for (int x = 31; x >= 0; x--)
  //   {
  //     sum = sum << 1;
  //     onOff = (matrix[7 - y][x]) ? 1 : 0;
  //     sum = sum ^ onOff;
  //     bin--;
  //     if (bin == -1)
  //     {
  //       LC.setRow(disp, y, sum);
  //       sum = 0;
  //       bin = 7;
  //       disp--;
  //     }
  //   }
  // }

  // Set Individual LED

  for (int x = 0; x < 32; x++)
  {
    int disp = x / 8;
    int newX = x % 8;
    for (int y = 0; y < 8; y++)
    {
      int onOff = (matrix[y][x]) ? 1 : 0;
      LC.setLed(disp, 7 - y, 7 - newX, onOff);
    }
  }
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

void updateGame()
{
  Serial.print("\n\n");
  int i, j;
  for (i = 0; i < 8; i++)
  {
    for (j = 0; j < 32; j++)
    {
      Serial.print(matrix[i][j]);
      if (matrix[i][j] > 0)
        matrix[i][j]--;
    }
    Serial.print("\n");
  }
}

void updateSnake(int snakeX, int snakeY)
{
  if (snakeX > 750 && snake.direction != DOWN)
  {
    snake.direction = UP;
  }
  else if (snakeX < 250 && snake.direction != UP)
  {
    snake.direction = DOWN;
  }
  else if (snakeY > 750 && snake.direction != RIGHT)
  {
    snake.direction = LEFT;
  }
  else if (snakeY < 250 && snake.direction != LEFT)
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

void check(int *gameOver)
{
  if (snake.x == apple.x && snake.y == apple.y)
  {
    snake.length++;
    snake.score += 1;
    newApple();
  }
  else if (matrix[snake.y][snake.x] > 0)
  {
    snake.lives--;
    initGame();
    if (snake.lives == 0)
    {
      *gameOver = 1;
    }
  }
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
  displayLogo();  
  delay(5000);

  initSnakeLives(3);
  initGame();

  int gameOver = 0;
  while (!gameOver)
  {
    updateSnakePositions();
    displayMatrix();

    int snakeX = analogRead(VRx);
    int snakeY = analogRead(VRy);
    updateSnake(snakeX, snakeY);

    updateGame();
    check(&gameOver);
    delay(50);
  }

  displayGameOver();
  delay(5000);
}
