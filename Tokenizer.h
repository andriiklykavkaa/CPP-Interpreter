//
// Created by Andrii Klykavka on 05.07.2025.
//

#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>

#include "Token.h"
#include "funcs.h"

class Tokenizer {
private:
public:
    Tokenizer() = default;
    ~Tokenizer() = default;
    std::vector<Token> tokenize(const std::string &text) {
        std::vector<Token> tokens;
        std::string s_token;

        size_t i;
        size_t len = text.length();
        for(i = 0; i < len; ++i) {
            if (text[i] == ' ' || text[i] == ',') {
                if(!s_token.empty()) {
                    try {
                        Token t = convertStrToToken(s_token);
                        tokens.push_back(t);
                        s_token.clear();
                    } catch (std::runtime_error e) {
                        std::cout << "Error during tokenization." << std::endl;
                        return std::vector<Token>{};
                    }
                }
            } else {
                s_token += text[i];
            }
        }

        if (!s_token.empty()) {
            try {
                Token t = convertStrToToken(s_token);
                tokens.push_back(t);
                s_token.clear();
            } catch (std::runtime_error e) {
                std::cout << "Error during tokenization." << std::endl;
                return std::vector<Token>{};
            }
        }

        return tokens;
    }

    static Token convertStrToToken(const std::string &s_t) {
        if (is_integer(s_t)) {
            int val = std::atoi(s_t.c_str());
            return NumToken(val);
        }

        if (s_t == "-")
            return FuncToken(1, f_sub);
        if (s_t == "+")
            return FuncToken(1, f_add);
        if (s_t == "*")
            return FuncToken(2, f_multiply);
        if (s_t == "/")
            return FuncToken(2, f_divide);
        if (s_t == "max")
            return FuncToken(3, f_max);
        if (s_t == "min")
            return FuncToken(3, f_min);

        throw std::runtime_error("Unknown token: " + s_t);
    }

    static bool is_integer(const std::string &s_t) {
        if (s_t.empty()) return false;
        size_t i = 0;
        if (s_t[i] == '-' || s_t[i] == '+') {
            if (s_t.size() == 1) return false;
            ++i;
        }

        for(; i < s_t.size(); ++i) {
            if (!isdigit(s_t[i])) return false;
        }
        return true;
    }
};


#endif //TOKENIZER_H
