cmake_minimum_required(VERSION 3.27)
project(Grammar_Parser)

set(CMAKE_CXX_STANDARD 17)

add_executable(Grammar_Parser main.cpp
        grammarParser.cpp
        grammarParser.h
        LL1GrammarChecker.cpp
        LL1GrammarChecker.h
        LL1ParserTable.cpp
        LL1ParserTable.h
        MainWindow.cpp
        MainWindow.h
)
cmake_minimum_required(VERSION 3.27)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)


set(CMAKE_PREFIX_PATH "F:/Qt/6.6.1/mingw_64")

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)
