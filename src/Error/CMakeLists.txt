add_library(Error
    Error.cpp
    ErrorHandler.cpp
)

target_include_directories(Error INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)