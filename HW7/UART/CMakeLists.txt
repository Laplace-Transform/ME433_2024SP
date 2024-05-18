add_executable(UART)

target_sources(UART PRIVATE UART.c)

# Pull in our pico_stdlib which pulls in commonly used features
target_link_libraries(UART pico_stdlib hardware_i2c hardware_adc hardware_uart)


# create map/bin/hex file etc.
pico_add_extra_outputs(UART)