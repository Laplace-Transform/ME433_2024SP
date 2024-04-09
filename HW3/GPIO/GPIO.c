#include <stdio.h>
#include "pico/stdlib.h"

#define INPUT_PIN 14
#define OUTPUT_PIN 15
int pinstate;


int main() {
    
    gpio_init(INPUT_PIN);
    gpio_init(OUTPUT_PIN);
    gpio_set_dir(INPUT_PIN, GPIO_IN);
    gpio_set_dir(OUTPUT_PIN, GPIO_OUT);

    while (1) {
        pinstate = gpio_get(INPUT_PIN);
    if (pinstate > 0){
            gpio_put(OUTPUT_PIN, 1);
        }
    else{
            gpio_put(OUTPUT_PIN, 0);
        }

    }
}