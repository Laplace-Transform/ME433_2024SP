// based on adafruit and sparkfun libraries

#include <stdio.h>
#include <string.h> // for memset
#include "font.h"
#include "ssd1306.h"
#include "hardware/i2c.h"
#include "pico/stdlib.h"
#include "hardware/adc.h"



#define MCP23008_ADDR 0b100000

#define MCP23008_IODIR 0x00
#define MCP23008_GPIO  0x09
#define MCP23008_OLAT  0x0A

#define I2C_SDA_PIN 4
#define I2C_SCL_PIN 5

#define LED_PIN PICO_DEFAULT_LED_PIN


unsigned char SSD1306_ADDRESS = 0b0111100; // 7bit i2c address
unsigned char ssd1306_buffer[513]; // 128x32/8. Every bit is a pixel except first byte

void ssd1306_setup();
void ssd1306_command(unsigned char c);
void ssd1306_update() ;
void ssd1306_drawPixel(unsigned char x, unsigned char y, unsigned char color);
void ssd1306_clear() ;

void draw_a_letter(unsigned char x, unsigned char y,char input);
void draw_a_string(unsigned char x, unsigned char y,char *input);


int main() {
    stdio_init_all();
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    adc_init(); // init the adc module
    gpio_init(26);
    adc_select_input(0); // select to read from ADC0

    i2c_init(i2c_default, 100000); //100 kHz
    gpio_set_function(I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL_PIN, GPIO_FUNC_I2C);

    ssd1306_setup();

    char message_ADC[50];
    char message_fps[50];


    while (1) {
        unsigned int t0 = to_us_since_boot(get_absolute_time());
        // gpio_put(LED_PIN, true);
        // sleep_ms(250);
        // gpio_put(LED_PIN, false);
        // sleep_ms(250);
        
        
        int result = adc_read();
        sprintf(message_ADC, "my var = %d", result);        
        draw_a_string(10,10,message_ADC);
 

        unsigned int t1 = to_us_since_boot(get_absolute_time());
        double interval= ((float)t1-(float)t0)/1000/1000;
        sprintf(message_fps, "%.3f fps", 1/interval); 
        draw_a_string(10,25,message_fps);
    }
}

void draw_a_letter(unsigned char x, unsigned char y,char input){
    for(int i=0;i<5;i++){
        unsigned char buff = ASCII[input-32][i];
        for(int j=0;j<8;j++){
            ssd1306_drawPixel(x+i,y+j,(buff>>j) & 0b1);
        }

    }
    ssd1306_update();
}

void draw_a_string(unsigned char x, unsigned char y,char *input){
    
    for (int m=0; input[m]!=0; m++) {
        for(int i=0;i<5;i++){
            unsigned char buff = ASCII[input[m]-32][i];
            for(int j=0;j<8;j++){
                ssd1306_drawPixel(x+i,y+j,(buff>>j) & 0b1);
            }

        }
        x = x + 5;

    }
    ssd1306_update();
}


void ssd1306_setup() {
    // first byte in ssd1306_buffer is a command
    ssd1306_buffer[0] = 0x40;
    // give a little delay for the ssd1306 to power up
    //_CP0_SET_COUNT(0);
    //while (_CP0_GET_COUNT() < 48000000 / 2 / 50) {
    //}
    sleep_ms(20);
    ssd1306_command(SSD1306_DISPLAYOFF);
    ssd1306_command(SSD1306_SETDISPLAYCLOCKDIV);
    ssd1306_command(0x80);
    ssd1306_command(SSD1306_SETMULTIPLEX);
    ssd1306_command(0x1F); // height-1 = 31
    ssd1306_command(SSD1306_SETDISPLAYOFFSET);
    ssd1306_command(0x0);
    ssd1306_command(SSD1306_SETSTARTLINE);
    ssd1306_command(SSD1306_CHARGEPUMP);
    ssd1306_command(0x14);
    ssd1306_command(SSD1306_MEMORYMODE);
    ssd1306_command(0x00);
    ssd1306_command(SSD1306_SEGREMAP | 0x1);
    ssd1306_command(SSD1306_COMSCANDEC);
    ssd1306_command(SSD1306_SETCOMPINS);
    ssd1306_command(0x02);
    ssd1306_command(SSD1306_SETCONTRAST);
    ssd1306_command(0x8F);
    ssd1306_command(SSD1306_SETPRECHARGE);
    ssd1306_command(0xF1);
    ssd1306_command(SSD1306_SETVCOMDETECT);
    ssd1306_command(0x40);
    ssd1306_command(SSD1306_DISPLAYON);
    ssd1306_clear();
    ssd1306_update();
}

// send a command instruction (not pixel data)
void ssd1306_command(unsigned char c) {
    //i2c_master_start();
    //i2c_master_send(ssd1306_write);
    //i2c_master_send(0x00); // bit 7 is 0 for Co bit (data bytes only), bit 6 is 0 for DC (data is a command))
    //i2c_master_send(c);
    //i2c_master_stop();

    uint8_t buf[2];
    buf[0] = 0x00;
    buf[1] =c;
    i2c_write_blocking(i2c_default, SSD1306_ADDRESS, buf, 2, false);
}

// update every pixel on the screen
void ssd1306_update() {
    ssd1306_command(SSD1306_PAGEADDR);
    ssd1306_command(0);
    ssd1306_command(0xFF);
    ssd1306_command(SSD1306_COLUMNADDR);
    ssd1306_command(0);
    ssd1306_command(128 - 1); // Width

    unsigned short count = 512; // WIDTH * ((HEIGHT + 7) / 8)
    unsigned char * ptr = ssd1306_buffer; // first address of the pixel buffer
    /*
    i2c_master_start();
    i2c_master_send(ssd1306_write);
    i2c_master_send(0x40); // send pixel data
    // send every pixel
    while (count--) {
        i2c_master_send(*ptr++);
    }
    i2c_master_stop();
    */

    i2c_write_blocking(i2c_default, SSD1306_ADDRESS, ptr, 513, false);
}

// set a pixel value. Call update() to push to the display)
void ssd1306_drawPixel(unsigned char x, unsigned char y, unsigned char color) {
    if ((x < 0) || (x >= 128) || (y < 0) || (y >= 32)) {
        return;
    }

    if (color == 1) {
        ssd1306_buffer[1 + x + (y / 8)*128] |= (1 << (y & 7));
    } else {
        ssd1306_buffer[1 + x + (y / 8)*128] &= ~(1 << (y & 7));
    }
}

// zero every pixel value
void ssd1306_clear() {
    memset(ssd1306_buffer, 0, 512); // make every bit a 0, memset in string.h
    ssd1306_buffer[0] = 0x40; // first byte is part of command
}

