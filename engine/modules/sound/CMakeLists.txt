add_library(sound_module MODULE
        SoundModule.cpp
)

rtype_module(sound_module)

install(
        FILES
        SoundModule.hpp
        DESTINATION
        include/sound_module
)

find_package(SFML COMPONENTS audio CONFIG REQUIRED)
target_link_libraries(sound_module LINK_PRIVATE sfml-audio engine)
