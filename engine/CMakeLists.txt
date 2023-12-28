set(HEADER_FILES
        include/engine/exception/ConfigurationException.hpp
        include/engine/tools/NumberUtilities.hpp
        include/engine/ecs/component/CollisionComponent.hpp
        include/engine/ecs/component/DamageComponent.hpp
        include/engine/ecs/component/HealthComponent.hpp
        include/engine/ecs/component/PlayerComponent.hpp
        include/engine/ecs/component/PositionComponent.hpp
        include/engine/ecs/component/SpeedComponent.hpp
        include/engine/ecs/component/ComponentType.hpp
        include/engine/ecs/entitiesTypes/Bullet.hpp
        include/engine/ecs/entitiesTypes/Monster.hpp
        include/engine/ecs/entitiesTypes/Starship.hpp
        include/engine/ecs/Entity.hpp
        include/engine/ecs/EntityManager.hpp
        include/engine/ecs/entityModule/IGameModule.hpp
        include/engine/ecs/entityModule/module/AAIModule.hpp
        include/engine/ecs/entityModule/module/AAudioModule.hpp
        include/engine/ecs/entityModule/module/ACinematicModule.hpp
        include/engine/ecs/entityModule/module/AMetricsModules.hpp
        include/engine/ecs/entityModule/module/AConsoleModule.hpp
        include/engine/network/NetworkMessage.hpp
        include/engine/network/UDPAdapter.hpp
        include/engine/modules/IModule.hpp
        include/engine/modules/ModuleLoader.hpp
)

set(SOURCE_FILES
        src/Logger.cpp
        src/tools/NumberUtilities.cpp
        src/network/NetworkMessage.cpp
        src/network/UDPAdapter.cpp
)

#set(CMAKE_CXX_CLANG_TIDY "clang-tidy")

add_library(engine STATIC ${SOURCE_FILES})

add_subdirectory(modules/sound)
add_subdirectory(modules/console)
add_subdirectory(modules/particle)
add_subdirectory(modules/graphical)

find_package(asio CONFIG REQUIRED)
target_link_libraries(engine PRIVATE asio::asio)
target_include_directories(engine PRIVATE include/engine)
target_include_directories(engine PUBLIC include)