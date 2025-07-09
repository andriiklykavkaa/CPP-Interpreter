cmake_minimum_required(VERSION 3.29)
project(Interpreter)

set(CMAKE_CXX_STANDARD 20)

find_package(Boost REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})

add_executable(Interpreter src/main.cpp
        src/Interpreter.h
        src/tokens/Token.h
        src/ShuntingYardHelper.h
        src/funcs/funcs.h
        src/Tokenizer.h
        src/Interpreter.cpp
        src/Tokenizer.cpp
        src/ShuntingYardHelper.cpp
        src/tokens/Token.cpp
        src/tokens/FuncInfo.h
        src/utils/overloaded.h
)
