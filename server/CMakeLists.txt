set(SOURCE_FILES
      Main.cpp)
      
add_executable(${PROJECT_NAME}_server ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME}_server LINK_PUBLIC engine)