set(HEADER_FILES
        include/engine/exception/ConfigurationException.hpp
        include/engine/tools/NumberUtilities.hpp
        include/engine/ecs/EntityFactory.hpp
        include/engine/ecs/components/CollisionComponent.hpp
        include/engine/ecs/components/DamageComponent.hpp
        include/engine/ecs/components/HealthComponent.hpp
        include/engine/ecs/components/PlayerComponent.hpp
        include/engine/ecs/components/PositionComponent.hpp
        include/engine/ecs/components/SpeedComponent.hpp
        include/engine/ecs/components/ComponentType.hpp
        include/engine/ecs/entitiesTypes/Bullet.hpp
        include/engine/ecs/entitiesTypes/Monster.hpp
        include/engine/ecs/entitiesTypes/Starship.hpp
        include/engine/ecs/Entity.hpp
        include/engine/ecs/EntityManager.hpp
        include/engine/gameModule/IGameModule.hpp
        include/engine/gameModule/AModules/AAIModule.hpp
        include/engine/gameModule/AModules/AAudioModule.hpp
        include/engine/gameModule/AModules/ACinematicModule.hpp
        include/engine/gameModule/AModules/AMetricsModules.hpp
        include/engine/gameModule/AModules/AConsoleModule.hpp)

set(SOURCE_FILES
        src/Logger.cpp
        src/tools/NumberUtilities.cpp)

set(CMAKE_CXX_CLANG_TIDY "clang-tidy")

add_library(engine STATIC ${SOURCE_FILES})

find_package(asio CONFIG REQUIRED)
target_link_libraries(engine PRIVATE asio::asio)
target_include_directories(engine PRIVATE include/engine)
target_include_directories(engine PUBLIC include)