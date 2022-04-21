#ifndef BREAKOUT_H
#define BREAKOUT_H

// Functions
void input(int matrix[8][32]);
void display(int matrix[8][32]);
void initBall();
void initPaddle();
void initGame(int matrix[8][32]);
void updateGame(int matrix[8][32]);
void gameLoop(int matrix[8][32]);

#endif
