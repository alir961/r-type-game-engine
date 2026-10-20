add_library(animation_module MODULE
        AnimationModule.cpp
)

rtype_module(animation_module)

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

find_package(SFML COMPONENTS window graphics CONFIG REQUIRED)
target_link_libraries(animation_module LINK_PRIVATE sfml-graphics sfml-window engine)
