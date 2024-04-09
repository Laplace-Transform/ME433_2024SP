#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"

#define INPUT_PIN 14
#define OUTPUT_PIN 15

int pinstate;

int main() {
    stdio_init_all();

    gpio_init(INPUT_PIN);
    gpio_init(OUTPUT_PIN);
    gpio_set_dir(INPUT_PIN, GPIO_IN);
    gpio_set_dir(OUTPUT_PIN, GPIO_OUT);

    adc_init(); // init the adc module
    adc_gpio_init(26); // set ADC0 pin to be adc input instead of GPIO
    adc_select_input(0); // select to read from ADC0
    
    
    
    while (!stdio_usb_connected()) {
        sleep_ms(100);
    }
    printf("Start!\n");
    
    
    while (1) {
        char readtimes[100];
        pinstate = gpio_get(INPUT_PIN);
        int message = adc_read();
        
        gpio_put(OUTPUT_PIN, 1);//LED on
        
        if(pinstate == 0){//pressed
            gpio_put(OUTPUT_PIN, 0);
            printf("enter a number of analog samples to take, between 1 and 100 : \r\n");
            scanf("%d", readtimes);
            printf("you entered: %d: \r\n", *readtimes);
            for (int i = 0; i<*readtimes; i++) {
                int message = adc_read();
                float message_volt=message*3.3/4096; 
                printf("reading %d: %f: \r\n",i,message_volt);
                sleep_ms(10);
            }
        }
    }
}