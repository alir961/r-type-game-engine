set(HEADER_FILES
      include/engine/Logger.hpp)
      
set(SOURCE_FILES
      src/Logger.cpp)
      
add_library(engine STATIC ${SOURCE_FILES})

target_include_directories(engine PRIVATE include/engine)
target_include_directories(engine PUBLIC include)