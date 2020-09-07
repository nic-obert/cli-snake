#include <stdio.h>
#include <ncurses.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>

#include "entities.c"
#include "input.c"
#include "settings.c"


pid_t splitProcess(int fd[2]) {
    /*
        - then splits the process
        - one process listens for keyboard input
        - the other process returns to the mainloop
    */

    pid_t pid = fork();

    if (pid == 0) {
        // pass to listen function the memory addres
        // of the read file descriptor
        listen(fd);
        // if the infinite loop terminates --> exit
        _exit(0);
    }
    return pid;
}


void mainLoop() {

    // initialize interprocess communication
    int input[2];
    // create the pipe
    if (pipe(input) != 0) _exit(1);
    // make the read from pipe non-blocking
    fcntl(input[0], F_SETFL, O_NONBLOCK);
    pid_t pid = splitProcess(input);
    

    // initialize entities
    Snake snake;
    snake.bits[0].x = WIN_WIDTH / 2 + START_X;
    snake.bits[0].y = WIN_HEIGHT / 2 + START_Y;
    snake.bitCount = 1;

    Apple apple;
    moveApple(&apple, &snake);

    int direction;
    char playing = 1;
    while (playing) {
        // sleep
        usleep(SLEEP);
        

        // read input and update entities
        //read(input[0], &direction, 1);
        autoSnake(&snake, &apple, &direction);
        updateSnake(&snake, direction);
        

        if (didEat(&snake, &apple)) {
            eat(&snake);
            moveApple(&apple, &snake);
        }



        // check for collisions


        // draw entities and refresh screen
        refreshScreen(&snake, &apple);
    }
}


int main()
{
    
    srand(time(NULL));

    initscr();
    noecho();

    mainLoop();

    endwin();

    return 0;
}

