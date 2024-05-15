#include <stdio.h>

#include "hardware/i2c.h"
#include "pico/binary_info.h"
#include "pico/stdlib.h"


#define MCP23008_ADDR 0b100000

#define MCP23008_IODIR 0x00
#define MCP23008_GPIO  0x09
#define MCP23008_OLAT  0x0A

#define I2C_SDA_PIN 4
#define I2C_SCL_PIN 5

#define LED_PIN PICO_DEFAULT_LED_PIN

void init_mcp23008();
void set_led(bool state);
bool read_button();

int main() {
    stdio_init_all();
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    i2c_init(i2c_default, 100000); //100 kHz
    gpio_set_function(I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL_PIN, GPIO_FUNC_I2C);

    init_mcp23008();

    while (1) {

        gpio_put(LED_PIN, true);
        sleep_ms(250);
        gpio_put(LED_PIN, false);
        sleep_ms(250);

        // Control GP7 LED based on GP0 button state
        set_led(!read_button());
        sleep_ms(250);
    }
}

void init_mcp23008() {
    uint8_t buf[] = {MCP23008_IODIR, 0x01}; // Set IODIR register, GP0 as input, others as output
    i2c_write_blocking(i2c_default, MCP23008_ADDR, buf, 2, false);
}

void set_led(bool state) {
    uint8_t buf[] = {MCP23008_OLAT, state << 7}; // Control LED by setting the highest bit of OLAT register
    i2c_write_blocking(i2c_default, MCP23008_ADDR, buf, 2, false);
}

bool read_button() {
    uint8_t reg = MCP23008_GPIO;
    uint8_t value;
    i2c_write_blocking(i2c_default, MCP23008_ADDR, &reg, 1, true); // Hold bus control
    i2c_read_blocking(i2c_default, MCP23008_ADDR, &value, 1, false); // Release bus control
    return (value & 0x01) != 0; // Return the state of GP0
}