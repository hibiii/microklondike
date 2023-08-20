#include "game.h"
#include "screen.h"
#include <stdint.h>
#include <stdio.h>

Game game_init (void) {
    Game out = {
        .tower1 = { 4, 3, 2, 1, 0},
        .tower2 = { 0 },
        .tower3 = { 0 }
    };
    return out;
}

void game_deinit(Game *_1) {
    (void) _1;
}

int game_draw(Game *this) {
    fputs(screen_clear_line, stdout);
    fputc('-', stdout);
    for (int i = 0; this->tower1[i]; i++) {
        fputc(this->tower1[i] + '0', stdout);
    }
    fputc('\n', stdout);

    fputs(screen_clear_line, stdout);
    fputc('-', stdout);
    for (int i = 0; this->tower2[i]; i++) {
        fputc(this->tower2[i] + '0', stdout);
    }
    fputc('\n', stdout);

    fputs(screen_clear_line, stdout);
    fputc('-', stdout);
    for (int i = 0; this->tower3[i]; i++) {
        fputc(this->tower3[i] + '0', stdout);
    }
    fputc('\n', stdout);

    fputs(screen_clear_line, stdout);
    if (this->selected) {
        fputc('#', stdout);
        fputc(this->selected + '0', stdout);
    }
    fputc('\n', stdout);

    screen_cursor_up(4);

    if (ferror(stdout)) {
        return -1;
    }
    return 0;
}



#define remove_from_tower GAME_C$remove_from_tower
static uint8_t remove_from_tower(uint8_t *tower) {
    if (tower[0] == 0) {
        return 0;
    }

    int i = 0;
    while (tower[i]) {
        i++;
    }
    if (i > 0) {
        i--;
    }
    int val = tower[i];
    tower[i] = 0;
    return val;
}

bool game_select_from_tower(Game *this, int tower) {
    if (this->selected) {
        return false;
    }

    switch (tower) {
    case 0:
        this->selected = remove_from_tower(this->tower1);
        break;
    case 1:
        this->selected = remove_from_tower(this->tower2);
        break;
    case 2:
        this->selected = remove_from_tower(this->tower3);
        break;
    }

    return (bool) this->selected;
}


#define put_on_tower GAME_C$put_on_tower
static bool put_on_tower(uint8_t *tower, uint8_t disc) {
    if (tower[0] == 0) {
        tower[0] = disc;
        return true;
    }
    int i = 0;
    while (tower[i]) {
        i++;
    }
    if (tower[i - 1] < disc) {
        return false;
    }
    tower[i] = disc;
    return true;
}

bool game_put_on_tower(Game *this, int tower) {
    if (!this->selected) {
        return false;
    }

    switch (tower) {
    case 0:
        if(put_on_tower(this->tower1, this->selected)) {
            this->selected = 0;
        }
        break;
    case 1:
        if(put_on_tower(this->tower2, this->selected)) {
            this->selected = 0;
        }
        break;
    case 2:
        if(put_on_tower(this->tower3, this->selected)) {
            this->selected = 0;
        }
        break;
    }

    return this->selected == 0;
}
