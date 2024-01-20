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
        Text.hpp
        Rectangle.hpp
        Sprite.hpp
        DESTINATION
        include/graphical_module
)

if (WIN32)
    set(SFML_STATIC_LIBRARIES TRUE)
    set(SFML_DIR C:/SFML/lib/cmake/SFML)
    find_package(SFML COMPONENTS window graphics REQUIRED)

    include_directories(C:/SFML/include)
    target_link_libraries(graphical_module
            sfml-graphics
            sfml-window
            engine
    )
endif ()

if (NOT WIN32)
    find_package(SFML COMPONENTS window graphics CONFIG REQUIRED)
    target_link_libraries(graphical_module LINK_PRIVATE sfml-graphics sfml-window engine)
endif()
