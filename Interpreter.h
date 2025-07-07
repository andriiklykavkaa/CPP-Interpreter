//
// Created by Andrii Klykavka on 05.07.2025.
//

#ifndef INTERPRETER_H
#define INTERPRETER_H
#include <iostream>
#include <boost/algorithm/string.hpp>

#include "ShuntingYarHelper.h"
#include "Token.h"
#include "Tokenizer.h"

class Interpreter {
private:
    enum CommandType {
        expr,
        var_dec,
        var_ass,
        def_dec
    };

    struct FuncDef {
        std::vector<std::string> args;
        std::string body;
    };


    ShuntingYardHelper sy_helper;
    Tokenizer tokenizer;

    std::unordered_map<std::string, int> var_env;
    std::unordered_map<???> def_env;

    static bool is_var_ass(const std::string &line) {
        if (line.find('=') != std::string::npos &&
            !line.starts_with( "var ") &&
            !line.starts_with("def ")) {
            size_t eq_pos = line.find('=');
            std::string left = line.substr(0, eq_pos);
            boost::trim(left);
            return is_identifier(left);
            }
        return false;
    }

    static bool is_identifier(const std::string &s) {
        if (s.empty() || !std::isalpha(s[0]))
            return false;
        for (char c : s)
            if (!std::isalnum(c) && c != '_') return false;
        return true;
    }

    int evaluate_expr(const std::string &expr) {
        std::vector<Token> tokens = tokenizer.tokenize(expr, var_env);
        const int value = sy_helper.calculate(tokens);
        return value;
    }

public:
    Interpreter(const ShuntingYardHelper &sy_helper = ShuntingYardHelper(), const Tokenizer &tokenizer = Tokenizer())
    : sy_helper(sy_helper)
    , tokenizer(tokenizer)
    {}
    ~Interpreter() = default;

    void interpret_line(const std::string &line) {
        std::string trimmed = line;
        boost::trim(trimmed);
        const CommandType type = identify_command(trimmed);
        switch (type) {
            case expr:
                handle_expr(trimmed);
                break;
            case var_dec:
                handle_var_dec(trimmed);
                break;
            case var_ass:
                handle_var_ass(trimmed);
                break;
            case def_dec:
                handle_def_dec(trimmed);
                break;
        }
        // types: expression, var creation, var assignation, func declaration
    }

    CommandType identify_command(const std::string &line) {
        if (line.starts_with("var "))
            return CommandType::var_dec;
        if (line.starts_with("def "))
            return CommandType::def_dec;
        if (is_var_ass(line))
            return CommandType::var_ass;
        return CommandType::expr;
    }

    void handle_expr(const std::string &line) {
        int value = evaluate_expr(line);
        std::cout << value << std::endl;
    }

    void handle_var_dec(const std::string &line) {
        size_t name_start = 4;
        size_t eq_pos = line.find('=', name_start);
        std::string var_name = line.substr(name_start, eq_pos - name_start);
        boost::trim(var_name);
        if (var_env.contains(var_name)) {
            std::cout << "Error: already declared variable: " << var_name << std::endl;
        }

        std::string expr = line.substr(eq_pos + 1);
        boost::trim(expr);

        int value = evaluate_expr(expr);
        var_env[var_name] = value;
    }

    void handle_var_ass(const std::string &line) {
        size_t eq_pos = line.find('=');
        std::string var_name = line.substr(0, eq_pos);
        std::string expr = line.substr(eq_pos + 1);
        boost::trim(var_name);
        boost::trim(expr);

        if (var_env.find(var_name) == var_env.end()) {
            std::cout << "Unrecognized variable: " << var_name << std::endl;
        } else {
            int value = evaluate_expr(expr);
            var_env[var_name] = value;
        }
    }

    void handle_def_dec(const std::string &line) {
        size_t start = 4;
        size_t open_p = line.find('(', start);
        size_t close_p = line.find(')', open_p);
        size_t open_b = line.find('{', close_p);
        size_t close_b = line.find('}', open_b);

        std::string def_name = line.substr(start, open_p - start);
        boost::trim(def_name);

        std::string s_args = line.substr(open_p + 1, close_p - open_p - 1);
        std::string body = line.substr(open_b + 1, close_b - open_b - 1);
        boost::trim(body);

        std::vector<std::string> args;
        boost::split(args, s_args, boost::is_any_of(","));
        for (auto &arg : args) boost::trim(arg);

        if (def_env.contains(def_name)) {
            std::cout << "Error: function already defined: " << def_name << std::endl;
            return;
        }

        def_env[def_name] = FuncDef{args, body};
    }
};

#endif //INTERPRETER_H
