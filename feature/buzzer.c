#include "../include/buzzer.h"
#include "pico/stdlib.h"

#define BUZZER_PIN 21

// inicializa o buzzer
void buzzer_init(void)
{
    gpio_init(BUZZER_PIN);
    gpio_set_dir(BUZZER_PIN, GPIO_OUT);
    gpio_put(BUZZER_PIN, 0);
}

// liga o buzzer
void buzzer_on(void)
{
    gpio_put(BUZZER_PIN, 1);
}

// Desliga o buzzer
void buzzer_off(void)
{
    gpio_put(BUZZER_PIN, 0);
}

void buzzer_beep(void)
{
    buzzer_on();
    sleep_ms(500);
    buzzer_off();
}
