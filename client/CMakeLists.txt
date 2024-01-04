set(SOURCE_FILES
        Main.cpp
        src/ClientViewport.cpp
        src/entities/GraphicEntity.cpp
        src/components/Background.cpp
        src/UDPClient.cpp
)

#set(CMAKE_CXX_CLANG_TIDY "clang-tidy")

add_executable(${PROJECT_NAME}_client ${SOURCE_FILES})

find_package(SFML COMPONENTS system window graphics audio CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME}_client LINK_PRIVATE sfml-system sfml-network sfml-graphics sfml-window sfml-audio)

target_link_libraries(${PROJECT_NAME}_client LINK_PRIVATE engine)
