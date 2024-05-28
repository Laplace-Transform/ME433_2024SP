// based on adafruit and sparkfun libraries

#include <stdio.h>
#include <string.h> // for memset

#include "pico/stdlib.h"
#include "hardware/uart.h"
#include "hardware/irq.h"


#define LED_PIN PICO_DEFAULT_LED_PIN

//set up UART
#define UART_ID uart0
#define BAUD_RATE 115200
#define DATA_BITS 8
#define STOP_BITS 1
#define PARITY    UART_PARITY_NONE
// We are using pins 0 and 1, but see the GPIO function select table in the
// datasheet for information on which other pins can be used.
#define UART_TX_PIN 0
#define UART_RX_PIN 1

#define MOTOR_IN1 7
#define MOTOR_IN2 8
#define MOTOR_IN4 9
#define MOTOR_IN3 10

char message_UART[50];


void on_uart_rx();
void forward();
void turnleft();
void turnright();

volatile int chars_index = 0;
volatile int mode = 0;


int main() {
    stdio_init_all();
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    gpio_init(MOTOR_IN1);
    gpio_init(MOTOR_IN2);
    gpio_init(MOTOR_IN3);
    gpio_init(MOTOR_IN4);

    gpio_set_dir(MOTOR_IN1, GPIO_OUT);
    gpio_set_dir(MOTOR_IN2, GPIO_OUT);    
    gpio_set_dir(MOTOR_IN3, GPIO_OUT);
    gpio_set_dir(MOTOR_IN4, GPIO_OUT);


    // Set up our UART with a basic baud rate.
    uart_init(UART_ID, 2400);
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);    

    int __unused actual = uart_set_baudrate(UART_ID, BAUD_RATE);
    // Set UART flow control CTS/RTS, we don't want these, so turn them off
    uart_set_hw_flow(UART_ID, false, false);
    // Set our data format
    uart_set_format(UART_ID, DATA_BITS, STOP_BITS, PARITY);
    // Turn off FIFO's - we want to do this character by character
    uart_set_fifo_enabled(UART_ID, false);
    // Set up a RX interrupt
    // We need to set up the handler first
    // Select correct interrupt for the UART we are using
    int UART_IRQ = UART_ID == uart0 ? UART0_IRQ : UART1_IRQ;
    // And set up and enable the interrupt handlers
    irq_set_exclusive_handler(UART_IRQ, on_uart_rx);
    irq_set_enabled(UART_IRQ, true);
    // Now enable the UART to send interrupts - RX only
    uart_set_irq_enables(UART_ID, true, false);
    // OK, all set up.
    // Lets send a basic string out, and then run a loop and wait for RX interrupts
    // The handler will count them, but also reflect the incoming data back with a slight change!
    uart_puts(UART_ID, "\nHello, uart interrupts\n");

    while (1) {



        tight_loop_contents();
    }
}


// RX interrupt handler
void on_uart_rx() {
    while (uart_is_readable(UART_ID)) {
        uint8_t ch = uart_getc(UART_ID);
        message_UART[chars_index] = ch;
        chars_index++;

        if (ch == '\n'){
            sscanf(message_UART,"%d",&mode);
            chars_index = 0;
        }
        
        
        
        if(mode <= 0.4){
            gpio_put(LED_PIN, false);
            turnright();

        }
        else if(mode >=0.6){
            gpio_put(LED_PIN, false);
            turnleft();
        }
        else{
            gpio_put(LED_PIN, true);    
            forward();
        }
    }
}


void forward(){
    gpio_put(MOTOR_IN1, false);
    gpio_put(MOTOR_IN2, true);
    gpio_put(MOTOR_IN3, false);
    gpio_put(MOTOR_IN4, true);
}

void turnleft(){
    gpio_put(MOTOR_IN1, true);
    gpio_put(MOTOR_IN2, false);
    gpio_put(MOTOR_IN3, false);
    gpio_put(MOTOR_IN4, true);
}

void turnright(){
    gpio_put(MOTOR_IN1, false);
    gpio_put(MOTOR_IN2, true);
    gpio_put(MOTOR_IN3, true);
    gpio_put(MOTOR_IN4, false);
}