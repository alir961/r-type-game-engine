add_library(graphical_module MODULE
        GraphicalModule.cpp
)

# Set the output directory for the module library
set_target_properties(graphical_module PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

install(
        FILES
        GraphicalModule.hpp
        DESTINATION
        include/graphical_module
)

target_link_libraries(graphical_module PRIVATE engine)