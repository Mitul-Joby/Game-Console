#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "snake.h"

struct Snake
{
    int x;
    int y;
    int length;
    int score;
    int lives;
} snake;

struct Apple
{
    int x;
    int y;
} apple;

void initSnakeLives(int lives)
{
    snake.lives = lives;
}

void initGame(int matrix[8][32])
{
    srand(time(NULL));
    snake.x = 15;
    snake.y = 3;
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
}

void updateGame(int matrix[8][32])
{
    matrix[snake.y][snake.x] = snake.length;
    matrix[apple.y][apple.x] = -1;
}

void newApple(int matrix[8][32])
{
    apple.x = rand() % 31;
    apple.y = rand() % 7;

    if (matrix[apple.y][apple.x] == 1)
    {
        newApple(matrix);
    }
}

void input(int matrix[8][32])
{
    char direction;
    printf("\nInput: ");
    scanf("%c", &direction);
    printf("\n");
    fflush(stdin);
    switch (direction)
    {
    case 'w':
        snake.y--;
        break;
    case 's':
        snake.y++;
        break;
    case 'a':
        snake.x--;
        break;
    case 'd':
        snake.x++;
        break;
    }
}

void display(int matrix[8][32])
{
    int i, j;
    for (i = 0; i < 8; i++)
    {
        for (j = 0; j < 32; j++)
        {
            if (matrix[i][j] == 0)
            {
                printf("0 ");
            }
            else
            {
                printf("1 ");
            }
            if (matrix[i][j] > 0)
                matrix[i][j]--;
        }
        printf("\n");
    }
}

void check(int matrix[8][32])
{
    if (snake.x == apple.x && snake.y == apple.y)
    {
        snake.length++;
        snake.score += 1;
        newApple(matrix);
    }
    else if (snake.x < 0 || snake.x > 31 || snake.y < 0 || snake.y > 7 || matrix[snake.y][snake.x] > 0)
    {
        snake.lives--;
        printf("\nYou lost a life!\n");
        initGame(matrix);
        if (snake.lives == 0)
        {
            printf("Game Over!\n");
            exit(0);
        }
    }
}
