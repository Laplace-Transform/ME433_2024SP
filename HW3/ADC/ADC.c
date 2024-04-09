#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"

#define INPUT_PIN 19
#define OUTPUT_PIN 20


int main() {
    
    gpio_init(INPUT_PIN);
    gpio_init(OUTPUT_PIN);
    gpio_set_dir(INPUT_PIN, GPIO_IN);
    gpio_set_dir(OUTPUT_PIN, GPIO_OUT);

    adc_init(); // init the adc module
    adc_gpio_init(26); // set ADC0 pin to be adc input instead of GPIO
    adc_select_input(0); // select to read from ADC0
    
    
    stdio_init_all();
    while (!stdio_usb_connected()) {
        sleep_ms(100);
    }
    printf("Start!\n");
    
    
    while (1) {

        int message = adc_read();
        
        printf("message: %d\r\n",message);

        sleep_ms(500);
    }
}