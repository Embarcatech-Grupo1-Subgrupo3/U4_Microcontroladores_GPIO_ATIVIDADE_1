#ifndef LED_H
#define LED_H

#include "pico/stdlib.h"

#define RED 12
#define GREEN 13
#define BLUE 11

#define LED_ON 1
#define LED_OFF 0

void init_all_leds(void);

void turn_on_red(void);
void turn_on_green(void);
void turn_on_blue(void);

void turn_off_red(void);
void turn_off_green(void);
void turn_off_blue(void);

void turn_on_all_leds(void);
void turn_off_all_leds(void);

#endif
