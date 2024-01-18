set(SOURCE_FILES
        Main.cpp
        src/ClientViewport.cpp
        src/entities/GraphicEntity.cpp
        src/components/Background.cpp
        src/UDPClient.cpp
)

#set(CMAKE_CXX_CLANG_TIDY "clang-tidy")

add_executable(${PROJECT_NAME}_client ${SOURCE_FILES})

if (WIN32)
    set(SFML_STATIC_LIBRARIES TRUE)
    set(SFML_DIR C:/SFML/lib/cmake/SFML)
    find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

    include_directories(C:/SFML/include)
    target_link_libraries(${PROJECT_NAME}_client
            sfml-system
            sfml-network
            sfml-graphics
            sfml-window
            sfml-audio
            engine
    )
endif ()

if (NOT WIN32)
    find_package(SFML COMPONENTS system window graphics audio CONFIG REQUIRED)
    target_link_libraries(${PROJECT_NAME}_client PRIVATE
            sfml-system
            sfml-network
            sfml-graphics
            sfml-window
            sfml-audio
            engine
    )
endif()
