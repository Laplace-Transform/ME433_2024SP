add_executable(I2C)

target_sources(I2C PRIVATE I2C.c)

# Pull in our pico_stdlib which pulls in commonly used features
target_link_libraries(I2C pico_stdlib hardware_spi)


# create map/bin/hex file etc.
pico_add_extra_outputs(I2C)