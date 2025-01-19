#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "pico/stdlib.h"

#define ROWS 4
#define COLS 4

void keyboard_init();
char keyboard_get_key();

#endif
