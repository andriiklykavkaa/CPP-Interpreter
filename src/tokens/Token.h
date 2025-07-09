#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <variant>
#include <vector>
#include <unordered_map>
#include <iostream>

// forward declarations
class Tokenizer;
class ShuntingYardHelper;

class NumToken {
private:
    int val;
public:
    explicit NumToken(const int val) : val(val) {}
    [[nodiscard]] int get_value() const { return val; }
};

class OpToken {
private:
    std::function<int(int)> func;
public:
    explicit OpToken(std::function<int(int)> func) : func(std::move(func)) {}
    [[nodiscard]] int apply(const int &a) const { return func(a); }
    std::function<int(int)>& get_op() { return func; }
};

class FuncToken {
private:
    unsigned priority;
    std::function<int(int, int)> func;
public:
    explicit FuncToken(unsigned priority, std::function<int(int, int)> func)
    : priority(priority), func(std::move(func)) {}
    [[nodiscard]] int apply(const int a, const int b) const { return func(a, b); }
    [[nodiscard]] unsigned get_priority() const { return priority; }
};

enum DelimTokenType {
    opens = 0,
    closes = 1
};

class DelimToken {
private:
    DelimTokenType type;
public:
    explicit DelimToken(DelimTokenType type) : type(type) {}
    [[nodiscard]] DelimTokenType get_type() const { return type; }
};

class VarToken {
private:
    std::string name;
public:
    explicit VarToken(std::string name) : name(std::move(name)) {}
    ~VarToken() = default;

    [[nodiscard]] const std::string& get_name() const {
        return name;
    }
};

class CustomFuncToken;

typedef std::variant<NumToken, OpToken, FuncToken, DelimToken, VarToken, CustomFuncToken> Token;

class CustomFuncToken {
private:
    std::string name;
    std::vector<std::string> args;
    std::vector<Token> body_tokens;

public:
    CustomFuncToken(std::string name,
                    std::vector<std::string> args,
                    std::vector<Token> body_tokens);

    [[nodiscard]] const std::string& get_name() const { return name; }
    [[nodiscard]] const std::vector<std::string>& get_args() const { return args; }
    [[nodiscard]] const std::vector<Token>& get_body_tokens() const { return body_tokens; }


    // int apply(const std::vector<int> &arg_values) const;
};

#endif //TOKEN_H
