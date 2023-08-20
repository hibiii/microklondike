#ifndef SCREEN_H
#define SCREEN_H

// [errors] nonzero for fail
int screen_init(void);
int screen_deinit(void);
int screen_cursor_up(int);

extern const char *screen_clear_line;

#endif
