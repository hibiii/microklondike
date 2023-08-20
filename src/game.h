#ifndef GAME_H
#define GAME_H

#include <stdint.h>

typedef struct {
    uint8_t tower1[5];
    uint8_t tower2[5];
    uint8_t tower3[5];
    uint8_t selected;
} Game;

// [errors] none
Game game_init (void);
void game_deinit (Game *);

// [errors] false for fail
bool game_select_from_tower(Game*, int);
bool game_put_on_tower(Game*, int);

// [errors] nonzero for fail
int game_draw(Game *);

#endif
