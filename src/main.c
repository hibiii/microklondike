#include "game.h"
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
    Game game = game_init();
    while (loops) {
        game_draw(&game);
        switch (c = fgetc(stdin)) {
        case 'q': // fallthrough
        case 'Q': // fallthrough
        case 27: // fallthrough
        case EOF:
            loops = false;
            break;
        case '1': // fallthrough
        case '2': // fallthrough
        case '3': // fallthrough
            if (game.selected) {
                game_put_on_tower(&game, c - '1');
            } else {
                game_select_from_tower(&game, c - '1');
            }
            break;
        default:
            ;
        }
    }
    game_deinit(&game);
}
