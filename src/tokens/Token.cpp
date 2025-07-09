//
// Created by Andrii Klykavka on 09.07.2025.
//

#include "Token.h"
#include "../utils/overloaded.h"
#include "../Tokenizer.h"
#include "../ShuntingYardHelper.h"

CustomFuncToken::CustomFuncToken(std::string name,
                                 std::vector<std::string> args,
                                 std::vector<Token> body_tokens)
        : name(std::move(name)),
          args(std::move(args)),
          body_tokens(std::move(body_tokens)) {}
//
// int CustomFuncToken::apply(const std::vector<int>& arg_values) const {
//     if (arg_values.size() != args.size()) {
//         std::cerr << "Function '" << name << "' called with wrong number of arguments\n";
//         return 0;
//     }
//
//     std::unordered_map<std::string, int> local_env;
//     for (size_t i = 0; i < args.size(); ++i)
//         local_env[args[i]] = arg_values[i];
//
//     ShuntingYardHelper helper;
//     Tokenizer tokenizer;
//     std::vector<Token> resolved_tokens;
//     for (const Token &token : body_tokens) {
//         resolved_tokens.push_back(std::visit(overloaded{
//             [&](const NumToken& t) -> Token {
//                 return t;
//             },
//             [&](const OpToken& t) -> Token {
//                 return t;
//             },
//             [&](const FuncToken& t) -> Token {
//                 return t;
//             },
//             [&](const DelimToken& t) -> Token {
//                 return t;
//             },
//             [&](const CustomFuncToken& t) -> Token {
//                 return t;
//             },
//             [&](const auto& t) -> Token {
//                 return t;
//             },
//
//             [&](const std::string& ident) -> Token {
//                 if (local_env.contains(ident)) {
//                     return NumToken(local_env[ident]);
//                 }
//                 throw std::runtime_error("Unknown identifier in function body: " + ident);
//             }
//         }, token));
//     }
//
//     return helper.calculate(resolved_tokens);
// }