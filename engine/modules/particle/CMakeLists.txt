add_library(particle_module MODULE
        ParticleModule.cpp
)

# Set the output directory for the module library
set_target_properties(particle_module PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

install(
        FILES
        ParticleModule.hpp
        DESTINATION
        include/particle_module
)

find_package(SFML COMPONENTS window graphics CONFIG REQUIRED)
target_link_libraries(particle_module LINK_PRIVATE sfml-graphics sfml-window)

target_link_libraries(particle_module PRIVATE engine)