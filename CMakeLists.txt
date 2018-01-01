cmake_minimum_required (VERSION 2.6)
project (sol)
set(CMAKE_BUILD_TYPE Debug)
add_subdirectory(external/variant)

add_executable(sol 
    src/main.cpp
    src/TokenType.cpp
    src/ErrorReporter.cpp
    src/CodeLocation.cpp
    src/Scanner.cpp
    src/SourceFile.cpp
    src/Parser.cpp
    src/AstPrinter.cpp
)
include_directories( 
    external/
)
target_link_libraries(sol mpark_variant)
