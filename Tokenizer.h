//
// Created by Andrii Klykavka on 06.07.2025.
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
    std::vector<Token> tokenize(const std::string &text) const {
        std::vector<Token> tokens;
        std::string s_token;

        auto process_token = [&](std::string &token) -> void {
            if(!token.empty()) {
                try {
                    Token t = convertStrToToken(token);
                    tokens.push_back(t);
                    token.clear();
                } catch (std::runtime_error &e) {
                    std::cout << "Error during tokenization." << std::endl;
                    tokens.clear();
                }
                token.clear();
            }
        };

        size_t i = 0;
        bool expect_unary = true;

        while(i < text.size()) {
            const char c = text[i];

            if (c == '(' || c == ')') {
                process_token(s_token);
                if (text[i] == '(') {
                    Token d_t = DelimToken(DelimTokenType::open);
                    tokens.push_back(d_t);
                    expect_unary = true;
                } else {
                    Token d_t = DelimToken(DelimTokenType::close);
                    tokens.push_back(d_t);
                    expect_unary = false;
                }
                ++i;
            }
            else if (c == ' ' || c == ',') {
                process_token(s_token);
                ++i;
            }
            else if(std::isdigit(c)) {
                s_token += c;
                ++i;

                while (i < text.size() && std::isdigit(text[i])) {
                    s_token += text[i];
                    ++i;
                }
                process_token(s_token);
                expect_unary = false;
            } else if (std::isalpha(c)) {
                s_token += c;
                ++i;

                while(i < text.size() && std::isalpha(text[i])) {
                    s_token += text[i];
                    ++i;
                }

                process_token(s_token);
                expect_unary = false;
            } else if (c == '+' || c == '-') {
                process_token(s_token);
                if (expect_unary) {
                    Token op_t = (c == '+') ? OpToken(o_positate) : OpToken(o_negate);
                    tokens.push_back(op_t);
                } else {
                    Token fn_t = (c == '+') ? FuncToken(1, f_add) : FuncToken(1, f_sub);
                    tokens.push_back(fn_t);
                    expect_unary = true;
                }
                ++i;

            }  else if (c == '*' || c == '/') {
                process_token(s_token);
                Token fn_t = (c == '*') ? FuncToken(2, f_multiply) : FuncToken(2, f_divide);
                tokens.push_back(fn_t);
                ++i;
                expect_unary = true;
            } else {
                std::cerr << "Unknown character: '" << c << "'" << std::endl;
                return {};
            }
        }

        process_token(s_token);
        return tokens;
    }


    static Token convertStrToToken(const std::string &s_t) {
        if (is_integer(s_t)) {
            return NumToken(std::atoi(s_t.c_str()));
        }

        if (s_t == "max")
            return FuncToken(3, f_max);
        if (s_t == "min")
            return FuncToken(3, f_min);

        throw std::runtime_error("Unknown token: " + s_t);
    }


    static bool is_integer(const std::string &s_t) {
        try {
            size_t pos;
            std::stoi(s_t, &pos);
            return true;
        } catch (const std::invalid_argument& e) {
            return false;
        }
    }
};


#endif //TOKENIZER_H
