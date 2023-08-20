#include "screen.h"

#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include <termios.h>
#include <unistd.h>


static struct {
    struct termios old, new;
    bool loaded;
} screen;


int screen_init(void) {
    if (tcgetattr(STDIN_FILENO, &screen.old)) {
        return -1;
    }
    screen.new = screen.old;
    screen.new.c_lflag = screen.new.c_lflag & ~ICANON & ~ECHO;
    screen.loaded = true;
    if (tcsetattr(STDIN_FILENO, TCSANOW, &screen.new)) {
        return -1;
    }
    for (int i = 4; i; i--) {
        fputc('\n', stdout);
    }
    screen_cursor_up(4);
    if (ferror(stdout)) {
        return -1;
    }
    return 0;
}


int screen_deinit(void) {
    if (screen.loaded) {
        (void) tcsetattr(STDIN_FILENO, TCSANOW, &screen.old);
    }
    return 0;
}


int screen_cursor_up(int amt) {
    fprintf(stdout, "\x1B[%dA", amt);
    return ferror(stdout);
}

const char *screen_clear_line = "\x1B[2K";
