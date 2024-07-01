cmake_minimum_required(VERSION 3.5)

project(scriptlang VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(src/Lexer)
add_subdirectory(src/Parser)
add_subdirectory(src/Interpreter)
add_subdirectory(src/Error)

add_executable(${PROJECT_NAME}
    src/app.cpp
)

target_compile_options(${PROJECT_NAME} PRIVATE /FS)

target_link_libraries(${PROJECT_NAME}
    Lexer
    Parser
    Interpreter
    Error
)