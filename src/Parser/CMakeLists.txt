add_library(Parser
    Node.cpp
    Parser.cpp
)

target_include_directories(Parser INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(Parser Lexer Error)