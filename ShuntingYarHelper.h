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
    typedef std::stack<FuncToken> FuncTokenStack;

    std::stack<OpToken> o_stack;
    std::stack<FuncTokenStack> f_stack_2d;
    std::vector<int> output;

public:
    ShuntingYardHelper() {
        f_stack_2d.emplace();
    }
    ~ShuntingYardHelper() = default;

    [[nodiscard]] int calculate(const std::vector<Token> &tokens) {

        for(Token token : tokens) {
            handle_token(token);
        }

        while (!f_stack_2d.empty()) {
            auto& top_stack = f_stack_2d.top();
            while(!top_stack.empty()) {
                apply_func_token(top_stack.top());
                top_stack.pop();
            }

            f_stack_2d.pop();
        }

        if (!o_stack.empty() || !f_stack_2d.empty() || output.size() != 1) {
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
                        while (!o_stack.empty()) {
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
                        auto& top_stack = f_stack_2d.top();
                        while (!top_stack.empty() && top_stack.top().get_priority() >= t.get_priority()) {
                            apply_func_token(top_stack.top());
                            top_stack.pop();
                        }
                        top_stack.push(t);
                    },

                    [this](const DelimToken &t) -> void {
                        if (t.get_type() == DelimTokenType::opens) {
                            f_stack_2d.emplace();
                        } else {
                            auto top_stack = f_stack_2d.top();
                            while(!top_stack.empty()) {
                                apply_func_token(top_stack.top());
                                top_stack.pop();
                            }
                            f_stack_2d.pop();
                        }
                    }
                }, token);
    }

    void reset_structures() {
        while (!o_stack.empty()) { o_stack.pop(); }
        while (!f_stack_2d.empty()) {
            auto& top = f_stack_2d.top();
            while(!top.empty()) top.pop();
            f_stack_2d.pop();
        }
        f_stack_2d.emplace();
        output.clear();
    }
};

#endif //SHUNTINGYARHELPER_H
