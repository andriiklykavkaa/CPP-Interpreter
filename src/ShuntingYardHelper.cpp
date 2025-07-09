//
// Created by Andrii Klykavka on 09.07.2025.
//

#include "ShuntingYardHelper.h"

#include "tokens/FuncInfo.h"
#include "utils/overloaded.h"

ShuntingYardHelper::ShuntingYardHelper() {
    f_stack_2d.emplace();
}

int ShuntingYardHelper::calculate(const std::vector<Token> &tokens,
    const std::unordered_map<std::string, int> &var_env,
    const std::unordered_map<std::string, FuncInfo> &def_env) {
    for (Token token : tokens) {
        handle_token(token, var_env, def_env);
    }

    while (!f_stack_2d.empty()) {
        auto &top_stack = f_stack_2d.top();
        while (!top_stack.empty()) {
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

void ShuntingYardHelper::apply_func_token(const FuncToken &t) {
    if (output.size() < 2) {
        std::cout << "Error applying function." << std::endl;
        return;
    }

    const int b = output.back(); output.pop_back();
    const int a = output.back(); output.pop_back();

    output.push_back(t.apply(a, b));
}

void ShuntingYardHelper::handle_token(Token &token,
    const std::unordered_map<std::string, int> &var_env,
    const std::unordered_map<std::string, FuncInfo> &def_env) {
    std::visit(overloaded{
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
            auto &top_stack = f_stack_2d.top();
            while (!top_stack.empty() && top_stack.top().get_priority() >= t.get_priority()) {
                apply_func_token(top_stack.top());
                top_stack.pop();
            }
            top_stack.push(t);
        },

        [this, &def_env](const DelimToken &t) -> void {
            if (t.get_type() == DelimTokenType::opens) {
                f_stack_2d.emplace();
            } else {
                auto top_stack = f_stack_2d.top();
                while (!top_stack.empty()) {
                    apply_func_token(top_stack.top());
                    top_stack.pop();
                }
                f_stack_2d.pop();

                if(!cf_stack.empty()) {
                    const CustomFuncToken custom_func = cf_stack.top();
                    cf_stack.pop();

                    size_t args_count = custom_func.get_args().size();
                    std::unordered_map<std::string, int> local_env;
                    size_t i;

                    for(i = 0; i < args_count; ++i) {
                        local_env[custom_func.get_args()[args_count - i - 1]] = output.back();
                        output.pop_back();
                    }

                    ShuntingYardHelper sy_helper;
                    int result = sy_helper.calculate(custom_func.get_body_tokens(), local_env, def_env);
                    output.push_back(result);
                }
            }
        },

        [this, &var_env](const VarToken &t) -> void {
            const std::string& name = t.get_name();
            if(!var_env.contains(name)) {
                std::cout << "Unrecognized variable. " << std::endl;
                return;
            }
            int val = var_env.at(name);
            while (!o_stack.empty()) {
                const OpToken op_t = o_stack.top();
                o_stack.pop();
                val = op_t.apply(val);
            }
            output.push_back(val);
        },

        [this, &def_env](const CustomFuncToken& t) -> void {
            cf_stack.push(t);
        },
    }, token);
}

void ShuntingYardHelper::reset_structures() {
    while (!o_stack.empty()) o_stack.pop();
    while(!cf_stack.empty()) cf_stack.pop();
    while (!f_stack_2d.empty()) {
        auto &top = f_stack_2d.top();
        while (!top.empty()) top.pop();
        f_stack_2d.pop();
    }
    f_stack_2d.emplace();
    output.clear();
}
