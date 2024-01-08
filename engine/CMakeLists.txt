set(HEADER_FILES
        include/engine/exception/ConfigurationException.hpp
        include/engine/tools/NumberUtilities.hpp
        include/engine/tools/Split.hpp
        include/engine/tools/SafeQueue.hpp
        include/engine/ecs/component/SizeComponent.hpp
        include/engine/ecs/component/SizeRectComponent.hpp
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
        include/engine/modules/IGraphicalModule.hpp
        include/engine/modules/ModuleProvider.hpp
        include/engine/modules/animation/IAnimationModule.hpp
)

set(SOURCE_FILES
        src/Logger.cpp
        src/tools/NumberUtilities.cpp
        src/tools/Split.cpp
        src/network/NetworkMessage.cpp
        src/network/UDPAdapter.cpp
        src/modules/ModuleProvider.cpp
        include/engine/tools/Thread.hpp
)

#set(CMAKE_CXX_CLANG_TIDY "clang-tidy")

add_library(engine STATIC ${SOURCE_FILES})

set_property(TARGET engine PROPERTY POSITION_INDEPENDENT_CODE ON)

add_subdirectory(modules/animation)
add_subdirectory(modules/sound)
add_subdirectory(modules/console)
add_subdirectory(modules/particle)
add_subdirectory(modules/graphical)

find_package(asio CONFIG REQUIRED)
target_link_libraries(engine PRIVATE asio::asio)
if (WIN32)
    target_link_libraries(engine PRIVATE ws2_32)
endif()
target_include_directories(engine PRIVATE include/engine)
target_include_directories(engine PUBLIC include)