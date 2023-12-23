cmake_minimum_required(VERSION 3.26)
project(r-type)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_CLANG_TIDY "clang-tidy")

set(SOURCE_FILES
        Main.cpp
        src/GameView.cpp
        src/entities/GraphicBullet.cpp
        src/entities/GraphicEntityFactory.cpp
        src/entities/GraphicMonster.cpp
        src/entities/GraphicStarship.cpp
)

include_directories(include)
#include_directories(../engine/include) <- NOTE : for the moment that is useless bcz we only use the entities from the ecs
include_directories(../engine/include/engine/ecs)

find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
add_executable(${PROJECT_NAME}_client ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME}_client LINK_PRIVATE engine)
target_link_libraries(${PROJECT_NAME}_client LINK_PRIVATE sfml-system sfml-network sfml-graphics sfml-window)