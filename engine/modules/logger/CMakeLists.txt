add_library(logger_module MODULE
        LoggerModule.cpp
)

rtype_module(logger_module)

install(
        FILES
        LoggerModule.hpp
        DESTINATION
        include/graphical_module
)

target_link_libraries(logger_module PRIVATE engine)
