cmake_minimum_required (VERSION 2.6)
project (sol)

add_executable(sol 
    src/main.cpp
    src/TokenType.cpp
    src/ErrorReporter.cpp
)
include_directories( 
    external/
)
