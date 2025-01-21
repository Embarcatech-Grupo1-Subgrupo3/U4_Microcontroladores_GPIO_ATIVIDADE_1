#include "../include/keyboard.h"

#include <stdio.h>
#include "pico/stdlib.h"

#define ROWS 4
#define COLS 4

unsigned int gpio_rows[ROWS] = {4, 8, 9, 28};
unsigned int gpio_cols[COLS] = {16, 17, 18, 19};

const char keymap[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};

void keyboard_init()
{
    for (int i = 0; i < ROWS; i++)
    {
        gpio_init(gpio_rows[i]);
        gpio_set_dir(gpio_rows[i], GPIO_OUT);
        gpio_put(gpio_rows[i], 1);
    }
    for (int j = 0; j < COLS; j++)
    {
        gpio_init(gpio_cols[j]);
        gpio_set_dir(gpio_cols[j], GPIO_IN);
        gpio_pull_up(gpio_cols[j]);
    }
}

char keyboard_get_key()
{
    for (int i = 0; i < ROWS; i++)
    {
        gpio_put(gpio_rows[i], 0);
        for (int j = 0; j < COLS; j++)
        {
            if (gpio_get(gpio_cols[j]) == 0)
            {
                while (gpio_get(gpio_cols[j]) == 0)
                    ;
                gpio_put(gpio_rows[i], 1);
                return keymap[i][j];
            }
        }
        gpio_put(gpio_rows[i], 1);
    }
    return '\0';
}
