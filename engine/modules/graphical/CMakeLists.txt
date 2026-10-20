add_library(graphical_module MODULE
        GraphicalModule.cpp
)

rtype_module(graphical_module)

install(
        FILES
        GraphicalModule.hpp
        Text.hpp
        Rectangle.hpp
        Sprite.hpp
        DESTINATION
        include/graphical_module
)

find_package(SFML COMPONENTS window graphics CONFIG REQUIRED)
target_link_libraries(graphical_module LINK_PRIVATE sfml-graphics sfml-window engine)
