set(SOURCE_FILES
      Main.cpp
      src/GameView.cpp)

set(CMAKE_CXX_CLANG_TIDY "clang-tidy")

find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)

add_executable(${PROJECT_NAME}_client ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME}_client LINK_PRIVATE engine)
target_link_libraries(${PROJECT_NAME}_client LINK_PRIVATE sfml-system sfml-network sfml-graphics sfml-window)