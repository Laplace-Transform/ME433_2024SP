#include <stdio.h>
#include <math.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "pico/binary_info.h"

#define CS 17
#define SCK 18
#define SDI 19

#define M_PI 3.14159265358979323846

static inline void cs_select() {
    asm volatile("nop \n nop \n nop");
    gpio_put(CS, 0);  // Active low
    asm volatile("nop \n nop \n nop");
}

static inline void cs_deselect() {
    asm volatile("nop \n nop \n nop");
    gpio_put(CS, 1);
    asm volatile("nop \n nop \n nop");
}

static void write_register(uint8_t reg, uint8_t data) {
    uint8_t buf[2];
    buf[0] = reg;
    buf[1] = data;
    cs_select();
    spi_write_blocking(spi_default, buf, 2);
    cs_deselect();
    sleep_ms(1);
}


int main() {

    stdio_init_all();

    spi_init(spi_default, 1 * 1000 * 1000);
    gpio_set_function(SCK, GPIO_FUNC_SPI);
    gpio_set_function(SDI, GPIO_FUNC_SPI);
      
    // // Make the SPI pins available to picotool
    // bi_decl(bi_2pins_with_func(SDI, SCK, GPIO_FUNC_SPI));

    gpio_init(CS);
    gpio_set_dir(CS, GPIO_OUT);
    gpio_put(CS, 1);

    // // Make the CS pin available to picotool
    // bi_decl(bi_1pin_with_name(CS, "SPI CS"));  
    
    int max = 1023;
    float time = 0;
    int sinwave = 0;
    int triangle = 0;
    while (1) {
        int sinwave = max/2 +  max/2*sin(2*M_PI*2*time);

        if (time<= 0.5) {
            triangle = 2*max * time;
        }
        else{
            triangle = 2*max  - 2*max *time;
        }

        time = time + 0.01;

        if (time >= 1){
            time = 0;
        }

        // bit shifting
        int portA = 0;
        int P = 0;
        P = P | (portA<<15);
        P = P | (0b111<<12);
        P = P | (sinwave<<2);
        int P1 = P>>8;
        int P2 = P & 0xff;

        write_register(P1, P2);
        sleep_ms(5);
        
        int portB = 1;
        P = 0;
        P = P | (portB<<15);
        P = P | (0b111<<12);
        P = P | (triangle<<2);
        P1 = P>>8;
        P2 = P & 0xff;

        write_register(P1, P2);

        sleep_ms(5);
        

        
   }

        // write_register(0b11111111, 0b111111 << 2);//write B
        // write_register(0b01111111, 0b111111 << 2);//write A
        
    // Chip select is active-low, so we'll initialise it to a driven-high state
}
