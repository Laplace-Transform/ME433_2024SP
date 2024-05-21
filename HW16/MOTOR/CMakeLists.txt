add_executable(MOTOR)

target_sources(MOTOR PRIVATE MOTOR.c)

# Pull in our pico_stdlib which pulls in commonly used features
target_link_libraries(MOTOR pico_stdlib hardware_uart)


# create map/bin/hex file etc.
pico_add_extra_outputs(MOTOR)