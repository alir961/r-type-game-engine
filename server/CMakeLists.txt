set(HEADER_FILES
        include/Arguments.hpp
        include/UDPServer.hpp
        include/UDPAdapter.hpp
        include/BinaryEncoder.hpp
        include/DataCompressor.hpp
        include/compression/HuffmanAlgorithm.hpp
        include/compression/LZ4Algorithm.hpp
        include/compression/RLEAlgorithm.hpp
        include/compression/IDataCompression.hpp)

set(SOURCE_FILES
        Main.cpp
        src/UDPServer.cpp
        src/UDPAdapter.cpp
        src/compression/LZ4Algorithm.cpp
        src/compression/RLEAlgorithm.cpp
        src/compression/HuffmanAlgorithm.cpp
        src/BinaryEncoder.cpp)

set(CMAKE_CXX_CLANG_TIDY "clang-tidy")

add_executable(${PROJECT_NAME}_server ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME}_server LINK_PUBLIC engine)