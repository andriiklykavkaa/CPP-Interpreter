//
// Created by Andrii Klykavka on 05.07.2025.
//

#ifndef SHUNTINGYARDHELPER_H
#define SHUNTINGYARDHELPER_H

#include <iostream>
#include <stack>
#include <vector>
#include <variant>

#include "tokens/FuncInfo.h"
#include "tokens/Token.h"

class ShuntingYardHelper {
private:
    typedef std::stack<FuncToken> FuncTokenStack;

    std::stack<OpToken> o_stack;
    std::stack<FuncTokenStack> f_stack_2d;
    std::stack<CustomFuncToken> cf_stack;
    std::vector<int> output;

    void apply_func_token(const FuncToken &t);
    void handle_token(Token &token,
    const std::unordered_map<std::string, int> &var_env,
    const std::unordered_map<std::string, FuncInfo> &def_env);

    void reset_structures();

public:
    ShuntingYardHelper();
    ~ShuntingYardHelper() = default;

    [[nodiscard]] int calculate(const std::vector<Token> &tokens,
    const std::unordered_map<std::string, int> &var_env,
    const std::unordered_map<std::string, FuncInfo> &def_env);
};

#endif // SHUNTINGYARDHELPER_H
