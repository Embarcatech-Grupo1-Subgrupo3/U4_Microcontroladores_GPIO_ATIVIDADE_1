#include <stdio.h>
#include "pico/stdlib.h"

#include "include/buzzer.h"
#include "include/keyboard.h"
#include "include/led.h"

int main(void)
{
    stdio_init_all();
    buzzer_init();
    keyboard_init();
    led_init();

    printf("Sistema inicializado.\n");

    while (true)
    {
        char key = keyboard_get_key();
        if (key == '1')
        {
            led_on(1);
            buzzer_on();
        }
        else
        {
            led_off(1);
            buzzer_off();
        }
    }

    return 0;
}
