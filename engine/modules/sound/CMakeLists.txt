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

if (WIN32)
    set(SFML_STATIC_LIBRARIES TRUE)
    set(SFML_DIR C:/SFML/lib/cmake/SFML)
    find_package(SFML COMPONENTS audio REQUIRED)

    include_directories(C:/SFML/include)
    target_link_libraries(sound_module
            sfml-audio
            engine
    )
endif ()

if (NOT WIN32)
    find_package(SFML COMPONENTS audio CONFIG REQUIRED)
    target_link_libraries(sound_module LINK_PRIVATE sfml-audio engine)
endif()
