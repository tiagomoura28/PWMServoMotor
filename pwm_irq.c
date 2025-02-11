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


    // Define o nível do 




/*

#define SERVO_PIN 22  // Pino GPIO para o servomotor
#define LED_PIN 12    // Pino GPIO para o LED RGB
#define PWM_FREQUENCY 50 // Frequência de 50Hz (período de 20ms)
#define CLOCK 125000000  // Clock do RP2040 (125MHz)
#define WRAP_VALUE (CLOCK / (PWM_FREQUENCY * 64)) // Cálculo do wrap considerando divisor de clock*/

/*
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
    sleep_ms(50);
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

*/
/*
#define LEDPin 12 //pino do LED conectado a GPIO como PWM

//tratamento da interrupção do PWM
void wrapHandler(){ 
    static int fade = 0; //nível de iluminação
    static bool rise = true; //flag para elevar ou reduzir a iluminação
    pwm_clear_irq(pwm_gpio_to_slice_num(LEDPin)); //resetar o flag de interrupção

    if(rise){ //caso a iluminação seja elevada
        fade++; //aumenta o nível de brilho
        if(fade > 255){ //caso o fade seja maior que 255
            fade = 255; //iguala fade a 255
            rise = false; //muda o flag rise para redução do nível de iluminação
        }
    }
    else{ //caso a iluminação seja reduzida
        fade--; //reduz o nível de brilho
        if(fade < 0){ //Icaso o fade seja menor que 0
            fade = 0; //iguala fade a 0
            rise = true; //muda o flag rise para elevação no nível de iluminação
        }
    }

    pwm_set_gpio_level(LEDPin, fade * fade); //define o ciclo ativo (Ton) de forma quadrática, para acentuar a variação de luminosidade.
}

//Configuração do PWM com interrupção
uint pwm_setup_irq(){

    gpio_set_function(LEDPin, GPIO_FUNC_PWM); //habilitar o pino GPIO como PWM
    uint sliceNum = pwm_gpio_to_slice_num(LEDPin); //obter o canal PWM da GPIO

    pwm_clear_irq(sliceNum); //resetar o flag de interrupção para o slice
    pwm_set_irq_enabled(sliceNum, true); //habilitar a interrupção de PWM para um dado slice
    irq_set_exclusive_handler(PWM_IRQ_WRAP, wrapHandler); //Definir um tipo de interrupção.
    // Esta interrupção (PWM_IRQ_WRAP) é gerada quando um contador de um slice atinge seu valor de wrap
    irq_set_enabled(PWM_IRQ_WRAP, true); //Habilitar ou desabilitar uma interrupção específica

    pwm_config config = pwm_get_default_config(); //obtem a configuração padrão para o PWM
    pwm_config_set_clkdiv(&config, 4.f); //define o divisor de clock do PWM
    pwm_init(sliceNum, &config, true); //inicializa o PWM com as configurações do objeto

    return sliceNum;
}

int main(){

    uint sliceNum = pwm_setup_irq(); //função que inicializa o PWM com interrupção por wrap

    while(1){

        printf("Interrupção do PWM ativa");
        pwm_set_irq_enabled(sliceNum, true); //habilita a interrupção
        sleep_ms(5000);
        printf("Interrupção do  PWM desativada"); //desabilita a interrupção
        pwm_set_irq_enabled(sliceNum, false);
        sleep_ms(5000);

    }
}
    */