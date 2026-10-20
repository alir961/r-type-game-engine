set(HEADER_FILES
        include/engine/exception/ConfigurationException.hpp
        include/engine/tools/NumberUtilities.hpp
        include/engine/tools/Split.hpp
        include/engine/tools/SafeQueue.hpp
        include/engine/tools/Thread.hpp
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
        include/engine/modules/graphical/IGraphicalModule.hpp
        include/engine/modules/ModuleProvider.hpp
        include/engine/modules/animation/IAnimationModule.hpp
        include/engine/modules/animation/IAnimation.hpp
        include/engine/modules/animation/Animation.hpp
        include/engine/modules/animation/PlayerAnimation.hpp
        include/engine/modules/animation/.hpp
        include/engine/modules/animation/IAnimationFactory.hpp
        include/engine/modules/graphical/AText.hpp
        include/engine/modules/graphical/ARectangle.hpp
        include/engine/modules/graphical/DataCommon.hpp
        include/engine/modules/graphical/ASprite.hpp
        include/engine/modules/logger/ILoggerModule.hpp
)

set(SOURCE_FILES
        src/Logger.cpp
        src/tools/NumberUtilities.cpp
        src/tools/Split.cpp
        src/network/NetworkMessage.cpp
        src/network/UDPAdapter.cpp
        src/modules/ModuleProvider.cpp
)

#set(CMAKE_CXX_CLANG_TIDY "clang-tidy")

add_library(engine STATIC ${SOURCE_FILES})

set_property(TARGET engine PROPERTY POSITION_INDEPENDENT_CODE ON)

add_subdirectory(modules/animation)
add_subdirectory(modules/sound)
add_subdirectory(modules/console)
add_subdirectory(modules/particle)
add_subdirectory(modules/graphical)
add_subdirectory(modules/logger)

find_package(asio CONFIG REQUIRED)
target_link_libraries(engine PRIVATE asio::asio)
if (WIN32)
    # Windows 10 API level for Asio, no min/max or GDI macros (ERROR) from windows.h, and M_PI from <cmath>
    target_compile_definitions(engine PUBLIC _WIN32_WINNT=0x0A00 NOMINMAX NOGDI WIN32_LEAN_AND_MEAN _USE_MATH_DEFINES)
endif()
target_include_directories(engine PRIVATE include/engine)
target_include_directories(engine PUBLIC include)
