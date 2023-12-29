add_library(console_module MODULE
        ConsoleModule.cpp
)

# Set the output directory for the module library
set_target_properties(console_module PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

install(
        FILES
        ConsoleModule.hpp
        DESTINATION
        include/console_module
)

target_link_libraries(console_module PRIVATE engine)