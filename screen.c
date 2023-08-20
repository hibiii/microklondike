#ifndef SCREEN_C
#define SCREEN_C

// [errors] nonzero for fail
#include <stdio.h>
int screen_init(void);
int screen_deinit(void);

#ifndef MAIN
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

#include <errno.h>
#include <termios.h>


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
    return 0;
}


int screen_deinit(void) {
    if (screen.loaded) {
        (void) tcsetattr(STDIN_FILENO, TCSANOW, &screen.old);
    }
    return 0;
}

#endif
#endif
