add_executable(TechCup)

target_sources(TechCup PRIVATE TechCup.c)

# Pull in our pico_stdlib which pulls in commonly used features
target_link_libraries(TechCup pico_stdlib hardware_uart)


# create map/bin/hex file etc.
pico_add_extra_outputs(TechCup)