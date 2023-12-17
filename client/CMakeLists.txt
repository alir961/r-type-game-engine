cmake_minimum_required(VERSION 3.26)
project(r-type_client)

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
include_directories(../engine/include)
include_directories(../engine/include/ecs)
include_directories(../engine/include/ecs/components)

add_executable(r-type_client ${SOURCE_FILES})

target_link_libraries(r-type_client engine)
target_link_libraries(r-type_client ${CONAN_LIBS})

add_custom_command(TARGET r-type_client POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:r-type_client>/assets)
