#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"

// Definição dos pinos GPIO para cada LED do semáforo
#define LED_VERMELHO 13
#define LED_AMARELO 12
#define LED_VERDE 11

// Índice que controla o estado do semáforo
int estado_atual = 0;

/**
 * Callback acionado pelo temporizador a cada 3 segundos.
 * Essa função desativa todos os LEDs antes de ativar o próximo
 * seguindo a sequência: Vermelho -> Amarelo -> Verde -> Vermelho.
 */
bool alternar_semaforo(struct repeating_timer *t)
{
    // Desliga todos os LEDs antes de acionar o próximo
    gpio_put(LED_VERMELHO, 0);
    gpio_put(LED_AMARELO, 0);
    gpio_put(LED_VERDE, 0);

    // Alterna o estado do semáforo
    switch (estado_atual)
    {
    case 0:
        gpio_put(LED_VERMELHO, 1);
        printf("Sinal Vermelho - PARE!\n");
        break;

    case 1:
        gpio_put(LED_AMARELO, 1);
        printf("Sinal Amarelo - ATENÇÃO!\n");
        break;

    case 2:
        gpio_put(LED_VERDE, 1);
        printf("Sinal Verde - SIGA!\n");
        break;
    }

    // Atualiza para o próximo estado, reiniciando ao chegar no último
    estado_atual = (estado_atual + 1) % 3;

    return true; // Mantém o temporizador ativo
}

int main()
{
    // Inicializa a comunicação serial para saída no terminal
    stdio_init_all();

    // Configura os pinos dos LEDs como saída
    gpio_init(LED_VERMELHO);
    gpio_set_dir(LED_VERMELHO, GPIO_OUT);

    gpio_init(LED_AMARELO);
    gpio_set_dir(LED_AMARELO, GPIO_OUT);

    gpio_init(LED_VERDE);
    gpio_set_dir(LED_VERDE, GPIO_OUT);

    // Liga o LED vermelho no início do programa
    gpio_put(LED_VERMELHO, 1);
    printf("Sistema do semáforo iniciado...\n");

    // Declara e configura o temporizador para alternar os LEDs a cada 3 segundos
    struct repeating_timer timer;
    add_repeating_timer_ms(3000, alternar_semaforo, NULL, &timer);

    // Loop principal mantém o programa rodando
    while (true)
    {
        sleep_ms(1000); // Espera 1 segundo antes de imprimir a mensagem
        printf("Aguardando próxima mudança no semáforo...\n");
    }
}
