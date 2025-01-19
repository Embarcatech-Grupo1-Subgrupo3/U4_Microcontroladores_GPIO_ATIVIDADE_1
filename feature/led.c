#include "../include/led.h"
#include "pico/stdlib.h"

#define RED 12
#define GREEN 13
#define BLUE 11

#define LED_ON 1
#define LED_OFF 0

// inicializar todos os leds
void init_all_leds(void)
{
    gpio_init(RED);
    gpio_init(GREEN);
    gpio_init(BLUE);

    gpio_set_dir(RED, GPIO_OUT);
    gpio_set_dir(GREEN, GPIO_OUT);
    gpio_set_dir(BLUE, GPIO_OUT);

    gpio_put(RED, LED_OFF);
    gpio_put(GREEN, LED_OFF);
    gpio_put(BLUE, LED_OFF);
}

// Acender LEDs individualmente
void turn_on_red(void)
{
    gpio_put(RED, LED_ON);
}

void turn_on_green(void)
{
    gpio_put(GREEN, LED_ON);
}

void turn_on_blue(void)
{
    gpio_put(BLUE, LED_ON);
}

// apagar LEDs individualmente
void turn_off_red(void)
{
    gpio_put(RED, LED_OFF);
}

void turn_off_green(void)
{
    gpio_put(GREEN, LED_OFF);
}

void turn_off_blue(void)
{
    gpio_put(BLUE, LED_OFF);
}

// acender todos os LEDs
void turn_on_all_leds(void)
{
    gpio_put(RED, LED_ON);
    gpio_put(GREEN, LED_ON);
    gpio_put(BLUE, LED_ON);
}

// apagar todos os LEDs
void turn_off_all_leds(void)
{
    gpio_put(RED, LED_OFF);
    gpio_put(GREEN, LED_OFF);
    gpio_put(BLUE, LED_OFF);
}
