cmake_minimum_required(VERSION 3.27)
project(Grammar_Parser)

set(CMAKE_CXX_STANDARD 17)

add_executable(Grammar_Parser main.cpp
        grammarParser.cpp
        grammarParser.h
)
