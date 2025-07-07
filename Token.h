//
// Created by Andrii Klykavka on 05.07.2025.
//

#ifndef TOKEN_H
#define TOKEN_H
#include <string>

class NumToken {
private:
    int val;
public:
    explicit NumToken(const int val) : val(val) {};
    ~NumToken() = default;

    [[nodiscard]] int get_value() const {
        return val;
    }
};

class OpToken {
private:
    std::function<int(int)> func;
public:
    explicit OpToken(std::function<int(int)> func)
    : func(std::move(func)) {}
    ~OpToken() = default;

    [[nodiscard]] int apply(const int &a) const {
        return func(a);
    }

    std::function<int(int)>& get_op() {
        return func;
    }
};

class FuncToken {
private:
    unsigned priority;
    std::function<int(int, int)> func;
public:
    explicit FuncToken(unsigned priority, std::function<int(int, int)> func)
    : priority(priority), func(std::move(func)) {}
    ~FuncToken() = default;

    [[nodiscard]] int apply(const int a, const int b) const {
        return func(a, b);
    }

    [[nodiscard]] unsigned get_priority() const {
        return priority;
    }
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
    ~DelimToken() = default;

    [[nodiscard]] DelimTokenType get_type() const {
        return type;
    }
};

typedef std::variant<NumToken, OpToken, FuncToken, DelimToken> Token;

#endif //TOKEN_H
