//
// Created by Andrii Klykavka on 05.07.2025.
//

#ifndef INTERPRETER_H
#define INTERPRETER_H
#include <stack>

#include "ShuntingYarHelper.h"
#include "Token.h"
#include "Tokenizer.h"

class Interpreter {
private:
    ShuntingYardHelper sy_helper;
    Tokenizer tokenizer;

public:
    Interpreter(const ShuntingYardHelper &sy_helper = ShuntingYardHelper(), const Tokenizer &tokenizer = Tokenizer())
    : sy_helper(sy_helper)
    , tokenizer(tokenizer)
    {}
    ~Interpreter() = default;

    void interprete_line(std::string &line) {
        std::vector<Token> tokens;
        tokens = tokenizer.tokenize(line);

        int result = sy_helper.calculate(tokens);
        std::cout << result << std::endl;
    }
};

#endif //INTERPRETER_H
