add_executable(ADC)

target_sources(ADC PRIVATE ADC.c)

# Pull in our pico_stdlib which pulls in commonly used features
target_link_libraries(ADC pico_stdlib hardware_adc)

pico_enable_stdio_usb(ADC 1)
pico_enable_stdio_uart(ADC 0)

# create map/bin/hex file etc.
pico_add_extra_outputs(ADC)