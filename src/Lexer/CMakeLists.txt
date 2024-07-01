add_library(Lexer
    Token.cpp
    Tokenizer.cpp
)

target_include_directories(Lexer INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(Lexer Error)