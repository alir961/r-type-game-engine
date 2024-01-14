set(HEADER_FILES
        include/Arguments.hpp
        include/UDPServer.hpp
        include/BinaryEncoder.hpp
        include/DataCompressor.hpp
        include/compression/HuffmanAlgorithm.hpp
        include/compression/LZ4Algorithm.hpp
        include/compression/RLEAlgorithm.hpp
        include/compression/IDataCompression.hpp
        include/Client.hpp
        include/game/GameLogic.hpp
        include/SessionManager.hpp)

set(SOURCE_FILES
        Main.cpp
        src/UDPServer.cpp
        src/compression/LZ4Algorithm.cpp
        src/compression/RLEAlgorithm.cpp
        src/compression/HuffmanAlgorithm.cpp
        src/BinaryEncoder.cpp
        src/SessionManager.cpp
        src/Client.cpp
        include/network/MessageParser.hpp
        src/network/MessageParser.cpp
        src/game/GameLogic.cpp
        include/game/EntityFactory.hpp)

#set(CMAKE_CXX_CLANG_TIDY "clang-tidy")

add_executable(${PROJECT_NAME}_server ${SOURCE_FILES})

find_package(asio CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME}_server PRIVATE asio::asio)

target_link_libraries(${PROJECT_NAME}_server LINK_PUBLIC engine)