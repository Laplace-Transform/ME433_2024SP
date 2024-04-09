add_executable(MAIN)

target_sources(MAIN PRIVATE MAIN.c)

# Pull in our pico_stdlib which pulls in commonly used features
target_link_libraries(MAIN pico_stdlib hardware_adc)

pico_enable_stdio_usb(MAIN 1)
pico_enable_stdio_uart(MAIN 0)

# create map/bin/hex file etc.
pico_add_extra_outputs(MAIN)