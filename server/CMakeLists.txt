set(SOURCE_FILES
        Main.cpp
        include/Arguments.hpp)

set(CMAKE_CXX_CLANG_TIDY "clang-tidy")

add_executable(${PROJECT_NAME}_server ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME}_server LINK_PUBLIC engine)