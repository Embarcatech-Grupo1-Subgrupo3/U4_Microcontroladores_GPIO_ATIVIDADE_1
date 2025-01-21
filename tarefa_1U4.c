#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"

// Definições de pinos e valores
#define ROWS 4
#define COLS 4

#define BUZZER_PIN 21
#define RED 12
#define GREEN 13
#define BLUE 11

#define LED_ON 1
#define LED_OFF 0

// Definição do mapeamento das teclas do teclado matricial
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

void buzzer_init(void)
{
    gpio_init(BUZZER_PIN);
    gpio_set_dir(BUZZER_PIN, GPIO_OUT);
}

// Configura o PWM no pino do buzzer com uma frequência especificada
void set_buzzer_frequency(uint pin, uint frequency)
{
    // Obter o slice do PWM associado ao pino
    uint slice_num = pwm_gpio_to_slice_num(pin);

    // Configurar o pino como saída de PWM
    gpio_set_function(pin, GPIO_FUNC_PWM);

    // Configurar o PWM com frequência desejada
    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, clock_get_hz(clk_sys) / (frequency * 4096)); // Calcula divisor do clock

    pwm_init(slice_num, &config, true);
    pwm_set_gpio_level(pin, 0); // Inicializa com duty cycle 0 (sem som)
}

// Função para tocar o buzzer por um tempo especificado (em milissegundos)
void play_buzzer(uint pin, uint frequency, uint duration_ms)
{
    set_buzzer_frequency(pin, frequency); // Configura a frequência
    pwm_set_gpio_level(pin, 32768);       // Liga o buzzer com 50% de duty cycle (meia potência)
    sleep_ms(duration_ms);                // Toca o buzzer por um tempo especificado
    pwm_set_gpio_level(pin, 0);           // Desliga o buzzer após o tempo
}

// Inicializa todos os LEDs
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

// Apagar LEDs individualmente
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

// Acender todos os LEDs
void turn_on_all_leds(void)
{
    gpio_put(RED, LED_ON);
    gpio_put(GREEN, LED_ON);
    gpio_put(BLUE, LED_ON);
}

// Apagar todos os LEDs
void turn_off_all_leds(void)
{
    gpio_put(RED, LED_OFF);
    gpio_put(GREEN, LED_OFF);
    gpio_put(BLUE, LED_OFF);
}

int main()
{
    stdio_init_all(); // inicializa entrada e saída padrão
    init_all_leds();  // inicializa todos os leds
    buzzer_init();    // inicializa o buzzer
    keyboard_init();  // inicializa o teclado matricial

    while (true)
    {
        char key = keyboard_get_key(); // captura a tecla pressionada

        switch (key)
        {
        case 'A':
            turn_on_red(); // acende o led vermelho
            turn_off_blue();
            turn_off_green();
            break;

        case 'B':
            turn_on_blue(); // acende o led azul
            turn_off_red();
            turn_off_green();
            break;

        case 'C':
            turn_on_green(); // acende o led verde
            turn_off_blue();
            turn_off_red();
            break;

        case 'D':
            turn_on_all_leds(); // acende todos os leds
            break;

        case '*':
            play_buzzer(BUZZER_PIN, 1000, 500); // Toca o buzzer a 1000 Hz por 500ms
            break;
        case '0':
            turn_off_all_leds(); // desliga todos os leds
        }

        sleep_ms(100); // pequeno delay para evitar múltiplas leituras
    }

    return 0;
}
