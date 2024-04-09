add_executable(CDC)

target_sources(CDC PRIVATE CDC.c)

# Pull in our pico_stdlib which pulls in commonly used features
target_link_libraries(CDC pico_stdlib hardware_adc)

pico_enable_stdio_usb(CDC 1)
pico_enable_stdio_uart(CDC 0)

# create map/bin/hex file etc.
pico_add_extra_outputs(CDC)