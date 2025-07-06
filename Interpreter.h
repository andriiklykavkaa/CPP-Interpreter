//
// Created by Andrii Klykavka on 05.07.2025.
//

#ifndef INTERPRETER_H
#define INTERPRETER_H
#include <stack>

#include "ShuntingYarHelper.h"
#include "Token.h"

class Interpreter {
private:
    ShuntingYardHelper sy_helper;
    std::stack<Token> tokens;

};

#endif //INTERPRETER_H
