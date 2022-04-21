#include <stdio.h>
#include <stdlib.h>
#include "breakout.h"

struct Game
{
    int lives;
    int score;
} game = {3, 0};

struct Ball
{
    int x;
    int y;
    int dx;
    int dy;
} ball;

struct Paddle
{
    int x;
    int y;
} paddle;

void input(int matrix[8][32])
{
    char direction;
    printf("\nInput: ");
    scanf("%c", &direction);
    printf("\n");
    fflush(stdin);
    switch (direction)
    {
    case 'a':
        if (paddle.x > 2)
            paddle.x--;
        break;
    case 'd':
        if (paddle.x < 29)
            paddle.x++;
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
            printf("%d ", matrix[i][j]);
            if (matrix[i][j] > 1)
                matrix[i][j] = 0;
        }
        printf("\n");
    }
}

void initBall()
{
    ball.x = 15;
    ball.y = 6;
    ball.dx = 1;
    ball.dy = 1;
}

void initPaddle()
{
    paddle.x = 15;
    paddle.y = 7;
}

void initGame(int matrix[8][32])
{
    initBall();
    initPaddle();
    int i, j;
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 32; j++)
        {
            matrix[i][j] = 1;
        }
    }
}

void updateGame(int matrix[8][32])
{
    matrix[paddle.y][paddle.x - 2] = 2;
    matrix[paddle.y][paddle.x - 1] = 2;
    matrix[paddle.y][paddle.x] = 2;
    matrix[paddle.y][paddle.x + 1] = 2;
    matrix[paddle.y][paddle.x + 2] = 2;

    matrix[ball.y][ball.x] = 3;
}

void gameLoop(int matrix[8][32])
{
    updateGame(matrix);

    display(matrix);

    input(matrix);

    if (ball.y > 0 && matrix[ball.y - 1][ball.x] == 1)
    {
        matrix[ball.y - 1][ball.x] = 0;
        game.score++;

        ball.dy = -ball.dy;
    }

    if (ball.y + 1 == 7 && (ball.x >= paddle.x - 2 && ball.x <= paddle.x + 2))
    {
        ball.dy = -ball.dy;
        if (ball.x < paddle.x - 1)
        {
            ball.dx = -1;
        }
        if (ball.x > paddle.x + 1)
        {
            ball.dx = +1;
        }
    }

    if (ball.x + ball.dx < 0 || ball.x + ball.dx > 31)
    {
        ball.dx = -ball.dx;
    }

    if (ball.y + ball.dy < 0)
    {
        ball.dy = -ball.dy;
    }

    if (ball.y + ball.dy > 7)
    {
        game.lives--;
        initBall();
        initPaddle();
    }
    else
    {
        ball.x += ball.dx;
        ball.y += ball.dy;
    }
}
