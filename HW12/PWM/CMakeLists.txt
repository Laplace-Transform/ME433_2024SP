add_executable(PWM)

target_sources(PWM PRIVATE PWM.c)

# Pull in our pico_stdlib which pulls in commonly used features
target_link_libraries(PWM pico_stdlib hardware_pwm)


# create map/bin/hex file etc.
pico_add_extra_outputs(PWM)