add_library(animation_module MODULE
        AnimationModule.cpp
)

# Set the output directory for the module library
set_target_properties(animation_module PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

install(
        FILES
        AnimationModule.hpp
        DESTINATION
        include/animation_module
)

find_package(SFML COMPONENTS window graphics CONFIG REQUIRED)
target_link_libraries(animation_module LINK_PRIVATE sfml-graphics sfml-window)

target_link_libraries(animation_module PRIVATE engine)
