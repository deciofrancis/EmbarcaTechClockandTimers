#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/time.h"

// Definição dos pinos GPIO usados para os LEDs e o botão
#define LED_AZUL 11
#define LED_VERMELHO 12
#define LED_VERDE 13
#define PINO_BOTAO 5

// Variáveis para controle dos LEDs e do processo de desligamento
bool leds_ativos = false;
int indice_led = 0;

// Função que verifica se o botão foi pressionado
// Realiza debounce para evitar múltiplos acionamentos devido a ruídos elétricos
bool botao_foi_pressionado()
{
    // Verifica se o botão foi pressionado (pino em nível baixo)
    if (gpio_get(PINO_BOTAO) == 0)
    {
        sleep_ms(50);                  // Atraso curto para evitar múltiplos registros do mesmo pressionamento
        if (gpio_get(PINO_BOTAO) == 0) // Verifica novamente após o atraso
        {
            // Espera o botão ser solto antes de retornar "true"
            while (gpio_get(PINO_BOTAO) == 0)
            {
                sleep_ms(10); // Atraso enquanto o botão estiver pressionado
            }
            return true; // Retorna "true" quando o botão foi pressionado e solto
        }
    }
    return false; // Retorna "false" caso o botão não tenha sido pressionado
}

// Função de callback que desliga os LEDs de forma sequencial, com intervalo de 3 segundos entre cada um
// Utiliza o temporizador do Raspberry Pi Pico para agendar os desligamentos
int64_t callback_desligar_leds(alarm_id_t id, void *user_data)
{
    if (indice_led == 0)
    {
        gpio_put(LED_AZUL, false); // Desliga o LED azul
        indice_led++;              // Avança para o próximo LED
        // Agenda o desligamento do próximo LED após 3 segundos
        add_alarm_in_ms(3000, callback_desligar_leds, NULL, false);
    }
    else if (indice_led == 1)
    {
        gpio_put(LED_VERMELHO, false); // Desliga o LED vermelho
        indice_led++;                  // Avança para o próximo LED
        // Agenda o desligamento do próximo LED após 3 segundos
        add_alarm_in_ms(3000, callback_desligar_leds, NULL, false);
    }
    else if (indice_led == 2)
    {
        gpio_put(LED_VERDE, false); // Desliga o LED verde
        leds_ativos = false;        // Marca que todos os LEDs foram desligados
    }
    return 0; // Retorna 0 para indicar que a função de callback foi executada com sucesso
}

int main()
{
    // Configura os pinos dos LEDs como saída (ligar/desligar)
    gpio_init(LED_AZUL);
    gpio_set_dir(LED_AZUL, GPIO_OUT);
    gpio_init(LED_VERMELHO);
    gpio_set_dir(LED_VERMELHO, GPIO_OUT);
    gpio_init(LED_VERDE);
    gpio_set_dir(LED_VERDE, GPIO_OUT);

    // Configura o pino do botão como entrada, com resistor pull-up para manter o pino em nível alto quando o botão não for pressionado
    gpio_init(PINO_BOTAO);
    gpio_set_dir(PINO_BOTAO, GPIO_IN);
    gpio_pull_up(PINO_BOTAO); // Ativa o resistor pull-up no pino do botão

    while (true)
    {
        // Verifica se o botão foi pressionado e se os LEDs ainda não foram ativados
        if (botao_foi_pressionado() && !leds_ativos)
        {
            // Acende todos os LEDs
            gpio_put(LED_AZUL, true);
            gpio_put(LED_VERMELHO, true);
            gpio_put(LED_VERDE, true);

            leds_ativos = true; // Marca que o processo de ativação dos LEDs foi iniciado
            indice_led = 0;     // Reseta o índice de controle dos LEDs

            // Inicia o processo de desligamento sequencial dos LEDs com um intervalo de 3 segundos
            add_alarm_in_ms(3000, callback_desligar_leds, NULL, false);
        }

        sleep_ms(10); // Atraso de 10ms para otimizar o uso da CPU e evitar sobrecarga de processamento
    }
}
