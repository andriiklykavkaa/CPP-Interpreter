//
// Created by Andrii Klykavka on 05.07.2025.
//

#ifndef SHUNTINGYARHELPER_H
#define SHUNTINGYARHELPER_H
#include <iostream>
#include <stack>

#include "Token.h"

template<class... Ts>
struct overloaded: Ts... {
  using Ts::operator()...;
};

class ShuntingYardHelper {
private:
    std::stack<OpToken> o_stack;
    std::stack<FuncToken> f_stack;
    std::vector<int> output;

public:
    ShuntingYardHelper() = default;
    ~ShuntingYardHelper() = default;

    [[nodiscard]] int calculate(const std::vector<Token> &tokens) {

        for(Token token : tokens) {
            handle_token(token);
        }

        while (!f_stack.empty()) {
            apply_func_token(f_stack.top());
            f_stack.pop();
        }

        if (!o_stack.empty() || !f_stack.empty() || output.size() != 1) {
            std::cout << "Error in inner sizing. Format is invalid." << std::endl;
            return 0;
        }
        int result = output.back();
        reset_structures();
        return result;
    }

    void apply_func_token(const FuncToken &t) {
        if (output.size() < 2) {
            std::cout << "Error applying function." << std::endl;
            return;
        }

        const int b = output.back();
        output.pop_back();
        const int a = output.back();
        output.pop_back();

        output.push_back(t.apply(a, b));


    }

    void handle_token(Token &token) {
        std::visit(overloaded
                {
                    [this](const NumToken &t) -> void {
                        int val = t.get_value();
                        if (!o_stack.empty()) {
                            const OpToken op_t = o_stack.top();
                            o_stack.pop();
                            val = op_t.apply(val);
                        }
                        output.push_back(val);
                    },
                    [this](OpToken &t) -> void {
                        o_stack.push(t);
                    },
                    [this](const FuncToken &t) -> void {
                        while (!f_stack.empty() && f_stack.top().get_priority() >= t.get_priority()) {
                            apply_func_token(f_stack.top());
                            f_stack.pop();
                        }
                        f_stack.push(t);
                    }
                }, token);
    }

    void reset_structures() {
        while (!o_stack.empty()) { o_stack.pop(); }
        while (!f_stack.empty()) { f_stack.pop(); }
        output.clear();
    }
};

#endif //SHUNTINGYARHELPER_H
