//
// Created by Andrii Klykavka on 06.07.2025.
//

#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>

#include "tokens/FuncInfo.h"
#include "tokens/Token.h"
#include "funcs/funcs.h"

class Tokenizer {
private:
    static bool is_integer(const std::string &s_t);

public:
    Tokenizer() = default;
    ~Tokenizer() = default;

    std::vector<Token> tokenize(
        const std::string &text,
        const std::unordered_map<std::string, int> &var_env,
        std::unordered_map<std::string, FuncInfo> &def_env
    ) const;

    static Token convertStrToToken(
        const std::string &s_t,
        const std::unordered_map<std::string, int> &var_env,
        const std::unordered_map<std::string, FuncInfo> &def_env
    );
};

#endif // TOKENIZER_H

