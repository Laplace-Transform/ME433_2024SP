add_executable(DAC)

target_sources(DAC PRIVATE DAC.c)

# Pull in our pico_stdlib which pulls in commonly used features
target_link_libraries(DAC pico_stdlib hardware_spi)


# create map/bin/hex file etc.
pico_add_extra_outputs(DAC)