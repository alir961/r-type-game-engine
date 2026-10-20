add_library(console_module MODULE
        ConsoleModule.cpp
)

rtype_module(console_module)

install(
        FILES
        ConsoleModule.hpp
        DESTINATION
        include/console_module
)

target_link_libraries(console_module PRIVATE engine)
