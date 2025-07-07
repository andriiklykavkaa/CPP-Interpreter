cmake_minimum_required(VERSION 3.29)
project(Interpreter)

set(CMAKE_CXX_STANDARD 20)

find_package(Boost REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})

add_executable(Interpreter main.cpp
        Interpreter.h
        Token.h
        ShuntingYarHelper.h
        funcs.h
        Tokenizer.h
        Tokenizer.h
)
