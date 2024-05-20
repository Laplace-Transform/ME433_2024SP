// based on adafruit and sparkfun libraries

#include "pico/stdlib.h"
#include "hardware/pwm.h" 

#define LED_PIN PICO_DEFAULT_LED_PIN
#define PWM_PIN 16


uint16_t PWM_init();
void move_angle(uint16_t warp);

int main() {
    stdio_init_all();
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    
    uint16_t wrap = PWM_init();


    while (1) {


        move_angle(wrap);

    }
}

uint16_t PWM_init(){    
    //125M/50000/50=50hz
    gpio_set_function(PWM_PIN, GPIO_FUNC_PWM);// Set the LED Pin to be PWM
    uint slice_num = pwm_gpio_to_slice_num(PWM_PIN); // Get PWM slice number
    float div = 50; // must be between 1-255
    pwm_set_clkdiv(slice_num, div); // divider
    uint16_t wrap = 50000; // when to rollover, must be less than 65535
    pwm_set_wrap(slice_num, wrap);
    pwm_set_enabled(slice_num, true); // turn on the PWM
    return wrap;
}

void move_angle(uint16_t wrap){
    int degree0 = wrap * 0.025;// set the duty cycle to 2.5% = 1250
    int degree180 = wrap * 0.125;// set the duty cycle to 12.5%  = 6250

    //6250-1250 = 5000, so we need 5000 steps in 2000ms

    for(int i = degree0; i<degree180;i=i+2){
        pwm_set_gpio_level(PWM_PIN,i);
        sleep_ms(1);
    }


    for(int i = degree180; i>degree0;i=i-2){
        pwm_set_gpio_level(PWM_PIN,i); 
        sleep_ms(1);
    }


}