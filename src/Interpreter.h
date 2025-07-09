//
// Created by Andrii Klykavka on 05.07.2025.
//

#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <iostream>
#include <boost/algorithm/string.hpp>
#include "ShuntingYardHelper.h"
#include "tokens/Token.h"
#include "Tokenizer.h"

class Interpreter {
private:
    enum CommandType {
        expr,
        var_dec,
        var_ass,
        def_dec
    };

    ShuntingYardHelper sy_helper;
    Tokenizer tokenizer;

    std::unordered_map<std::string, int> var_env;
    std::unordered_map<std::string, FuncInfo> def_env;

    static bool is_var_ass(const std::string &line);
    static bool is_identifier(const std::string &s);
    int evaluate_expr(const std::string &expr);
    CommandType identify_command(const std::string &line);

    void handle_expr(const std::string &line);
    void handle_var_dec(const std::string &line);
    void handle_var_ass(const std::string &line);
    void handle_def_dec(const std::string &line);

public:
    Interpreter(const ShuntingYardHelper &sy_helper = ShuntingYardHelper(),
                const Tokenizer &tokenizer = Tokenizer());
    ~Interpreter() = default;

    void interpret_line(const std::string &line);
};

#endif //INTERPRETER_H
