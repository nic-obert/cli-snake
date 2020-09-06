#pragma once

#include <ncurses.h>
#include <unistd.h>


char listen(int* fd) {
    while (1) {
        // read key and send it to parent process
        int key = getch();
        write(fd[1], &key, 1);
    }
}
