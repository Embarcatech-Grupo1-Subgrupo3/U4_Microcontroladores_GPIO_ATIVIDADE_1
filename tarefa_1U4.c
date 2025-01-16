#include <stdio.h>
#include "pico/stdlib.h"

#include "include/buzzer.h"
#include "include/keyboard.h"
#include "include/led.h"

int main(void)
{
    buzzer_init();
    keyboard_init();
    led_init();

    printf("Sistema inicializado.\n");

    while (1)
    {
        int key = keyboard_read();
        if (key == 1)
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
