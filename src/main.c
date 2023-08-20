#include "screen.h"

#include <errno.h>
#include <signal.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static void handle_sigint (int);

static void game_loop(void);

int main (void) {
    if (screen_init()) {
        fprintf(stderr, "error: screen init: %s\n", strerror(errno));
        return 1;
    }
    if (signal(SIGINT, handle_sigint) == SIG_ERR) {
        fprintf(stderr, "error: signal install: disabled for SIGINT\n");
        return 1;
    };

    game_loop();

    (void) screen_deinit();
    return 0;
}


static void handle_sigint (int sig) {
    (void) sig;
    screen_deinit();
    exit(130);
}


static void game_loop(void) {
    bool loops = true;
    char c = ' ';
    while (loops) {
        fputc(c, stdout);
        fputc('\r', stdout);
        switch (c = fgetc(stdin)) {
        case 'q': // fallthrough
        case 'Q': // fallthrough
        case 27: // fallthrough
        case EOF:
            loops = false;
            break;
        default:
            ;
        }
    }
}
