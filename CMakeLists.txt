cmake_minimum_required(VERSION 3.29)
project(Interpreter)

set(CMAKE_CXX_STANDARD 20)

add_executable(Interpreter main.cpp
        Interpreter.h
        Token.h
        ShuntingYarHelper.h
        funcs.h
        Tokenizer.h
        Tokenizer.h)
