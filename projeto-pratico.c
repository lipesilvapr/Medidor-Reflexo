#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/i2c.h" // Inclui o driver I2C
#include "include/ssd1306.h"

// Definições das GPIOs
#define LED_VERDE 11
#define LED_AZUL 12
#define LED_VERMELHO 13
#define BOTAO_A 5

// Configuração do I2C
#define I2C_PORT i2c1
#define I2C_SDA 14 // Pino SDA (ajuste conforme necessário)
#define I2C_SCL 15 // Pino SCL (ajuste conforme necessário)
#define OLED_ADDRESS 0x3C

// Função para inicializar os pinos GPIO
void setup_gpio() {
    // Configura os LEDs como saída
    gpio_init(LED_VERDE);
    gpio_init(LED_AZUL);
    gpio_init(LED_VERMELHO);
    gpio_set_dir(LED_VERDE, GPIO_OUT);
    gpio_set_dir(LED_AZUL, GPIO_OUT);
    gpio_set_dir(LED_VERMELHO, GPIO_OUT);

    // Configura o botão como entrada com pull-up
    gpio_init(BOTAO_A);
    gpio_set_dir(BOTAO_A, GPIO_IN);
    gpio_pull_up(BOTAO_A);
}

// Função para acender um LED específico
void acender_led(uint8_t led) {
    gpio_put(LED_VERDE, 0);
    gpio_put(LED_AZUL, 0);
    gpio_put(LED_VERMELHO, 0);
    if (led == LED_VERDE) {
        gpio_put(LED_VERDE, 1);
    } else if (led == LED_AZUL) {
        gpio_put(LED_AZUL, 1);
    } else if (led == LED_VERMELHO) {
        gpio_put(LED_VERMELHO, 1);
    }
}

// Função para apagar todos os LEDs
void apagar_leds() {
    gpio_put(LED_VERDE, 0);
    gpio_put(LED_AZUL, 0);
    gpio_put(LED_VERMELHO, 0);
}

// Função para gerar um intervalo aleatório entre 1 e 5 segundos
uint32_t gerar_intervalo_aleatorio() {
    return (rand() % 5000) + 1000; // Intervalo entre 1000ms (1s) e 5000ms (5s)
}

// Função para configurar o I2C
void setup_i2c() {
    // Inicializa o I2C no barramento especificado
    i2c_init(I2C_PORT, 400 * 1000); // Frequência de 400 kHz
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);
}

int main() {
    // Inicializa o sistema
    stdio_init_all();
    srand(time(NULL)); // Inicializa o gerador de números aleatórios

    // Configura os GPIOs
    setup_gpio();

    // Configura o I2C
    setup_i2c();

    // Configura o display OLED
    ssd1306_t display;
    ssd1306_init(&display, 128, 64, false, OLED_ADDRESS, I2C_PORT);
    ssd1306_config(&display);

    // Limpa o display
    ssd1306_fill(&display, false);
    ssd1306_send_data(&display);

    while (1) {
        // Limpa o display antes de exibir "Aguarde..."
        ssd1306_fill(&display, false);

        // Exibe mensagem inicial no display
        ssd1306_draw_string(&display, "Aguarde...", 10, 20);
        ssd1306_send_data(&display);

        // Gera um intervalo aleatório e aguarda
        uint32_t intervalo = gerar_intervalo_aleatorio();
        sleep_ms(intervalo);

        // Acende o LED verde
        acender_led(LED_VERDE);

        // Registra o tempo inicial
        uint32_t tempo_inicial = time_us_32();

        // Aguarda o botão ser pressionado
        while (gpio_get(BOTAO_A)) {
            tight_loop_contents(); // Loop vazio para economizar CPU
        }

        // Apaga o LED
        apagar_leds();

        // Calcula o tempo de reação
        uint32_t tempo_final = time_us_32();
        uint32_t tempo_reacao = (tempo_final - tempo_inicial) / 1000; // Converte para ms

        // Limpa o display antes de exibir o tempo de reação
        ssd1306_fill(&display, false);

        // Exibe o tempo de reação no display
        char mensagem[20];
        snprintf(mensagem, sizeof(mensagem), "Tempo: %lu ms", tempo_reacao);
        ssd1306_draw_string(&display, mensagem, 10, 20);
        ssd1306_send_data(&display);

        // Aguarda 3 segundos antes de reiniciar
        sleep_ms(3000);
    }

    return 0;
}