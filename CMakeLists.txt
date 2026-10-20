cmake_minimum_required(VERSION 3.16)
project(r-type)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (MSVC)
    add_compile_options(/utf-8 /bigobj)
endif()

# Engine modules are loaded at runtime from build/out/engine/modules/<name>/lib<name>_module.so (.dll on
# Windows), see ModuleProvider.hpp: same name on every platform and no per-configuration subfolder.
function(rtype_module target)
    set_target_properties(${target} PROPERTIES
            PREFIX "lib"
            LIBRARY_OUTPUT_DIRECTORY "$<1:${CMAKE_CURRENT_BINARY_DIR}>"
            RUNTIME_OUTPUT_DIRECTORY "$<1:${CMAKE_CURRENT_BINARY_DIR}>"
            WINDOWS_EXPORT_ALL_SYMBOLS ON
    )
endfunction()

# Executables land in build/out/<client|server>/ with every generator, so the scripts find them.
function(rtype_executable target)
    set_target_properties(${target} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "$<1:${CMAKE_CURRENT_BINARY_DIR}>")
endfunction()

add_subdirectory(engine)
add_subdirectory(server)
add_subdirectory(client)
