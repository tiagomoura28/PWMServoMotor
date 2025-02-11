#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"


#define SERVO_PIN 22  // Definição do pino do servomotor
#define PWM_FREQUENCY 50 // Definição da frequência do PWM para controle do servo
#define CLOCK 125000000  // Frequência do clock principal do RP2040
#define WRAP_VALUE (CLOCK / (PWM_FREQUENCY * 64)) // Cálculo do valor máximo do contador do PWM (período do PWM)

// Definições dos pulsos correspondentes as ângulos
#define PULSO_0   500    // Posição aproximada de 0 graus
#define PULSO_90  1470   // Posição aproximada de 90 graus
#define PULSO_180 2400   // Posição aproximada de 180 graus

//Define o ângulo do servo convertendo a largura do pulso para nível PWM.
 
void set_angulo_servo(uint slice, uint16_t larguraDoPulso) {
    pwm_set_gpio_level(SERVO_PIN, (larguraDoPulso * WRAP_VALUE) / 20000);
}

//Configura o PWM no pino do servomotor. 
void setup_pwm() {
    gpio_set_function(SERVO_PIN, GPIO_FUNC_PWM);  // Define o pino como saída PWM
    uint slice = pwm_gpio_to_slice_num(SERVO_PIN); // Obtém o slice do PWM associado ao pino
    pwm_set_wrap(slice, WRAP_VALUE);  // Define o período do PWM
    pwm_set_clkdiv(slice, 64.0f);  // Define o divisor de clock para ajuste da frequência
    pwm_set_enabled(slice, true);  // Ativa o PWM
}

int main() {
    stdio_init_all();  // Inicializações
    setup_pwm();  // Configura o PWM
    uint slice = pwm_gpio_to_slice_num(SERVO_PIN); // Obtém o slice do PWM
    // Define posições fixas do servo com um tempo de espera de 5 segundos em cada posição
    sleep_ms(10);
    printf("Posição: 180 graus\n");
    set_angulo_servo(slice, PULSO_180);    
    sleep_ms(5000);

    set_angulo_servo(slice, PULSO_90);
    printf("Posição: 90 graus\n");
    sleep_ms(5000);

    set_angulo_servo(slice, PULSO_0);
    printf("Posição: 0 graus\n");
    sleep_ms(5000);

    // Movimentação suave entre 0 e 180 graus repetidamente
    while (true) {
        // Movimenta de 0 a 180 graus gradualmente
        printf("Movimentação suave entre 0 e 180 graus\n");
        for (uint16_t pulso = PULSO_0; pulso <= PULSO_180; pulso += 5) {
            set_angulo_servo(slice, pulso);
            sleep_ms(10);  // Pequeno atraso para suavidade
        }
        
        // Movimenta de 180 a 0 graus gradualmente
        printf("Movimentação suave entre 180 e 0 graus\n");
        for (uint16_t pulso = PULSO_180; pulso >= PULSO_0; pulso -= 5) {
            set_angulo_servo(slice, pulso);
            sleep_ms(10);  // Pequeno atraso para suavidade
        }
    }

    return 0;
}
