add_library(particle_module MODULE
        ParticleModule.cpp
)

rtype_module(particle_module)

install(
        FILES
        ParticleModule.hpp
        DESTINATION
        include/particle_module
)

find_package(SFML COMPONENTS window graphics CONFIG REQUIRED)
target_link_libraries(particle_module LINK_PRIVATE sfml-graphics sfml-window engine)
