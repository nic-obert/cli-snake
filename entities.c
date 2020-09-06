#pragma once

#include <ncurses.h>

#include "settings.c"


// APPLE
typedef struct {
    unsigned char x, y;
} Apple;


// BIT
typedef struct {
    unsigned char x, y;
} Bit;


// SNAKE
typedef struct {
    Bit bits[100];
    unsigned int bitCount;
} Snake;


void moveApple(Apple* apple) {
    apple->x = rand() % WIN_WIDTH + START_X;
    apple->y = rand() % WIN_HEIGHT + START_Y;
}


void updateSnake(Snake* snake, char direction) {

    // move the snake's body
    // this loop iterates in reverse over the snake's bits
    for (unsigned int bit = snake->bitCount; bit != 0; bit--) {
        // inherit previous bit's position
        snake->bits[bit].x = snake->bits[bit-1].x;
        snake->bits[bit].y = snake->bits[bit-1].y;
    }

    // move the snake's head
    switch (direction)
    {

    case 'w':
        if (snake->bits[0].y > START_Y)
            snake->bits[0].y --;
        break;

    case 's':
        if (snake->bits[0].y < END_Y)
            snake->bits[0].y ++;
        break;
    case 'a':
        if (snake->bits[0].x > START_X)
            snake->bits[0].x --;
        break;
    case 'd':
        if (snake->bits[0].x < END_X)
            snake->bits[0].x ++;
        break;
    }
}


void refreshScreen(Snake* snake, Apple* apple) {
    // clear the screen
    clear();


    // draw the playground
    unsigned char x, y;

    mvprintw(START_Y, START_X, "/");

    for (x = START_X+1; x < END_X; x++)
        printw("-");

    mvprintw(START_Y, END_X, "\\");

    for (y = START_Y+1; y < END_Y; y++)
        mvprintw(y, x, "|");

    mvprintw(END_Y, END_X, "/");

    move(y, START_X+1);
    for (x = END_X-1; x > START_X; x--)
        printw("-");
    
    mvprintw(END_Y, START_X, "\\");

    for (y = START_Y+1; y < END_Y; y++)
        mvprintw(y, x, "|");


    // draw the snake
    for (unsigned int bit = 1; bit < snake->bitCount; bit++)
        mvprintw(snake->bits[bit].y, snake->bits[bit].x, "o");
    mvprintw(snake->bits[0].y, snake->bits[0].x, "@");

    // draw the apple
    mvprintw(apple->y, apple->x, "#");


    // draw the score
    mvprintw(SCORE_Y, SCORE_X, "Score: %d", snake->bitCount);

    // move the cursor in a place it does not cover the playground
    move(0, 0);
    refresh();
}


void eat(Snake* snake) {
    snake->bitCount ++;
}


char didEat(Snake* snake, Apple* apple) {
    if (snake->bits[0].x == apple->x)
        if (snake->bits[0].y == apple->y)
            return 1;
    return 0;
}

