add_executable(GPIO)

target_sources(GPIO PRIVATE GPIO.c)

# Pull in our pico_stdlib which pulls in commonly used features
target_link_libraries(GPIO pico_stdlib hardware_adc)


# create map/bin/hex file etc.
pico_add_extra_outputs(GPIO)