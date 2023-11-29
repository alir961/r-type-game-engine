set(HEADER_FILES
      include/engine/Logger.hpp)
      
set(SOURCE_FILES
        src/Logger.cpp
        src/tools/NumberUtilities.cpp)

set(CMAKE_CXX_CLANG_TIDY "clang-tidy")

add_library(engine STATIC ${SOURCE_FILES})

target_include_directories(engine PRIVATE include/engine)
target_include_directories(engine PUBLIC include)