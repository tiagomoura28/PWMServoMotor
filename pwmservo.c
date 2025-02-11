#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

#define SERVO_PIN 22  // Pino GPIO para o servomotor
#define LED_PIN 12    // Pino GPIO para o LED RGB
#define PWM_FREQUENCY 50 // Frequência de 50Hz (período de 20ms)
#define CLOCK 125000000  // Clock do RP2040 (125MHz)
#define WRAP_VALUE (CLOCK / (PWM_FREQUENCY * 64)) // Cálculo do wrap considerando divisor de clock

void set_servo_angle(uint slice, uint level) {
    pwm_set_gpio_level(SERVO_PIN, level);
}

void set_led_color(uint slice, uint level) {
    pwm_set_gpio_level(LED_PIN, level);
}

int main() {
    stdio_init_all();
    
    // Configuração do pino para PWM
    gpio_set_function(SERVO_PIN, GPIO_FUNC_PWM);
    gpio_set_function(LED_PIN, GPIO_FUNC_PWM);
    uint slice = pwm_gpio_to_slice_num(SERVO_PIN);
    uint led_slice = pwm_gpio_to_slice_num(LED_PIN);
    
    // Configuração do PWM
    pwm_set_wrap(slice, WRAP_VALUE);
    pwm_set_clkdiv(slice, 64.0f);
    pwm_set_enabled(slice, true);

    pwm_set_wrap(led_slice, WRAP_VALUE);
    pwm_set_clkdiv(led_slice, 64.0f);
    pwm_set_enabled(led_slice, true);

    // Requisito 2: Posição 180 graus (2400µs)
    printf("Posição: 180 graus\n");
    set_servo_angle(slice, (2400 * WRAP_VALUE) / 20000); // 2.400µs = 180 graus
    set_led_color(led_slice, (2400 * WRAP_VALUE) / 20000); // Ajuste do LED RGB
    sleep_ms(5000); // Aguardar 5 segundos
    
    // Requisito 3: Posição 90 graus (1470µs)
    printf("Posição: 90 graus\n");
    set_servo_angle(slice, (1470 * WRAP_VALUE) / 20000); // 1.470µs = 90 graus
    set_led_color(led_slice, (1470 * WRAP_VALUE) / 20000); // Ajuste do LED RGB
    sleep_ms(5000); // Aguardar 5 segundos
    
    // Requisito 4: Posição 0 graus (500µs)
    printf("Posição: 0 graus\n");
    set_servo_angle(slice, (500 * WRAP_VALUE) / 20000); // 500µs = 0 graus
    set_led_color(led_slice, (500 * WRAP_VALUE) / 20000); // Ajuste do LED RGB
    sleep_ms(5000); // Aguardar 5 segundos
    
    do{// Requisito 5: Movimentação suave entre 0 e 180 graus
    printf("Movimentação suave entre 0 e 180 graus\n");
    for (int pulse = 500; pulse <= 2400; pulse += 5) {
        set_servo_angle(slice, (pulse * WRAP_VALUE) / 20000);
        set_led_color(led_slice, (pulse * WRAP_VALUE) / 20000); // Sincronizando o LED com o movimento
        sleep_ms(10); // Atraso de 10ms
    }
    for (int pulse = 2400; pulse >= 500; pulse -= 5) {
        set_servo_angle(slice, (pulse * WRAP_VALUE) / 20000);
        set_led_color(led_slice, (pulse * WRAP_VALUE) / 20000); // Sincronizando o LED com o movimento
        sleep_ms(10); // Atraso de 10ms
    }}while(true);
    
    // Fim do programa
    printf("Movimentação concluída.\n");

    return 0;
}
