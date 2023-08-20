#define MAIN
#include "screen.c"

#include <errno.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static void handle_sigint (int);

int main (void) {
    if (screen_init()) {
        fprintf(stderr, "error: screen init: %s\n", strerror(errno));
        return 1;
    }
    if (signal(SIGINT, handle_sigint) == SIG_ERR) {
        fprintf(stderr, "error: signal install: disabled for SIGINT\n");
        return 1;
    };
    printf("press any key to continue\n");
    fgetc(stdin);
    (void) screen_deinit();
    return 0;
}


static void handle_sigint (int sig) {
    (void) sig;
    screen_deinit();
    exit(130);
}
