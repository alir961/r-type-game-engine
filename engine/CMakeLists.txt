set(HEADER_FILES
        include/engine/exception/ConfigurationException.hpp
        include/engine/tools/NumberUtilities.hpp)

set(SOURCE_FILES
        src/Logger.cpp
        src/tools/NumberUtilities.cpp)

set(CMAKE_CXX_CLANG_TIDY "clang-tidy")

add_library(engine STATIC ${SOURCE_FILES})

find_package(asio CONFIG REQUIRED)
target_link_libraries(engine PRIVATE asio::asio)
target_include_directories(engine PRIVATE include/engine)
target_include_directories(engine PUBLIC include)