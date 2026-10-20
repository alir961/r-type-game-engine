add_library(animation_module MODULE
        AnimationModule.cpp
)

# Set the output directory for the module library
set_target_properties(animation_module PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

install(
        FILES
        AAnimation.hpp
        AnimationModule.hpp
        AnimationFactory.hpp
        entity/PlayerAnimation.hpp
        entity/BulletAnimation.hpp
        entity/MonsterAnimation.hpp
        entity/BulletStarshipAnimation.hpp
        entity/StarshipAnimation.hpp
        entity/StaticAnimation.hpp
        entity/ExplosionAnimation.hpp
        DESTINATION
        include/animation_module
)

if (WIN32)
        set(SFML_STATIC_LIBRARIES TRUE)
        set(SFML_DIR C:/SFML/lib/cmake/SFML)
        find_package(SFML COMPONENTS window graphics REQUIRED)

        include_directories(C:/SFML/include)
        target_link_libraries(animation_module
                sfml-graphics
                sfml-window
                engine
        )
endif ()

if (NOT WIN32)
        find_package(SFML COMPONENTS window graphics CONFIG REQUIRED)
        target_link_libraries(animation_module LINK_PRIVATE sfml-graphics sfml-window engine)
endif()
