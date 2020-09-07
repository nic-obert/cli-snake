#pragma once

#include <ncurses.h>

#include "settings.c"

#define head snake->bits[0]


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
    Bit bits[WIN_WIDTH * WIN_HEIGHT];
    unsigned int bitCount;
} Snake;


void moveApple(Apple* apple, Snake* snake) {
    while (1) {
        apple->x = rand() % WIN_WIDTH + START_X;
        apple->y = rand() % WIN_HEIGHT + START_Y;
        for (unsigned int bit = 0; bit < snake->bitCount; bit++) {
            if (snake->bits[bit].x != apple->x)
                if (snake->bits[bit].y != apple->y)
                 return;
        }
    }

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
        if (head.y > START_Y)
            head.y --;
        else head.y = END_Y;
        break;

    case 's':
        if (head.y < END_Y)
            head.y ++;
        else head.y = START_Y;
        break;
    case 'a':
        if (head.x > START_X)
            head.x --;
        else head.x = END_X;
        break;
    case 'd':
        if (head.x < END_X)
            head.x ++;
        else head.x = START_X;
        break;
    }
}


void autoSnake(Snake* snake, Apple* apple, int* direction) {
    if (head.x < apple->x)
        *direction = 'd';
    else if (head.x > apple->x)
        *direction = 'a';
    else if (head.y < apple->y)
        *direction = 's';
    else if (head.y > apple->y)
        *direction = 'w';
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
    mvprintw(head.y, head.x, "@");

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
    if (head.x == apple->x)
        if (head.y == apple->y)
            return 1;
    return 0;
}

