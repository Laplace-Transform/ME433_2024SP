add_executable(PICOtoZero)

target_sources(PICOtoZero PRIVATE PICOtoZero.c)

# Pull in our pico_stdlib which pulls in commonly used features
target_link_libraries(PICOtoZero pico_stdlib hardware_uart)


# create map/bin/hex file etc.
pico_add_extra_outputs(PICOtoZero)