set(SOURCE_FILES
      Main.cpp)
      
add_executable(${PROJECT_NAME}_client ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME}_client LINK_PRIVATE engine)