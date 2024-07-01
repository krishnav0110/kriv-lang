add_library(Interpreter
    Interpreter.cpp
    RuntimeVal.cpp
)

target_include_directories(Interpreter INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(Interpreter Parser)