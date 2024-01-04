add_library(sound_module MODULE
        SoundModule.cpp
)

# Set the output directory for the module library
set_target_properties(sound_module PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

install(
        FILES
        SoundModule.hpp
        DESTINATION
        include/sound_module
)

find_package(SFML COMPONENTS audio CONFIG REQUIRED)
target_link_libraries(sound_module LINK_PRIVATE sfml-audio)

target_link_libraries(sound_module PRIVATE engine)