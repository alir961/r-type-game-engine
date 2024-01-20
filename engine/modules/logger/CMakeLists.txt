add_library(logger_module MODULE
        LoggerModule.cpp
)

# Set the output directory for the module library
set_target_properties(logger_module PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

install(
        FILES
        LoggerModule.hpp
        DESTINATION
        include/graphical_module
)

target_link_libraries(logger_module PRIVATE engine)