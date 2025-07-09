//
// Created by Andrii Klykavka on 09.07.2025.
//

#include "Tokenizer.h"

#include "funcs/funcs.h"

bool Tokenizer::is_integer(const std::string &s_t) {
    try {
        size_t pos;
        std::stoi(s_t, &pos);
        return true;
    } catch (const std::invalid_argument& e) {
        return false;
    }
}

std::vector<Token> Tokenizer::tokenize(
    const std::string &text,
    const std::unordered_map<std::string, int> &var_env,
    std::unordered_map<std::string, FuncInfo> &def_env
) const {
    std::vector<Token> tokens;
    std::string s_token;

    auto process_token = [&](std::string &token) -> void {
        if (!token.empty()) {
            try {
                Token t = convertStrToToken(token, var_env, def_env);
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

    while (i < text.size()) {
        const char c = text[i];

        if (c == '(' || c == ')') {
            process_token(s_token);
            if (c == '(') {
                tokens.push_back(DelimToken(DelimTokenType::opens));
                expect_unary = true;
            } else {
                tokens.push_back(DelimToken(DelimTokenType::closes));
                expect_unary = false;
            }
            ++i;
        } else if (c == ' ' || c == ',') {
            process_token(s_token);
            ++i;
            if (c == ',') expect_unary = true;
        } else if (std::isdigit(c)) {
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
            while (i < text.size() && std::isalpha(text[i])) {
                s_token += text[i];
                ++i;
            }
            process_token(s_token);
            expect_unary = false;
        } else if (c == '+' || c == '-') {
            process_token(s_token);
            if (expect_unary) {
                tokens.push_back((c == '+') ? OpToken(o_positate) : OpToken(o_negate));
            } else {
                tokens.push_back((c == '+') ? FuncToken(1, f_add) : FuncToken(1, f_sub));
                expect_unary = true;
            }
            ++i;
        } else if (c == '*' || c == '/') {
            process_token(s_token);
            tokens.push_back((c == '*') ? FuncToken(2, f_multiply) : FuncToken(2, f_divide));
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

Token Tokenizer::convertStrToToken(
    const std::string &s_t,
    const std::unordered_map<std::string, int> &var_env,
    const std::unordered_map<std::string, FuncInfo> &def_env
) {
    if (is_integer(s_t)) {
        return NumToken(std::atoi(s_t.c_str()));
    }

    if (var_env.contains(s_t)) {
        return VarToken(s_t);
    }

    if (def_env.contains(s_t)) {
        return CustomFuncToken(s_t, def_env.at(s_t).args, def_env.at(s_t).tokenized_body);
    }

    throw std::runtime_error("Unknown token: " + s_t);
}
