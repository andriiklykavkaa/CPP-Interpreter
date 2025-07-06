//
// Created by Andrii Klykavka on 05.07.2025.
//

#ifndef FUNCS_H
#define FUNCS_H
#include <functional>

// Operator token functions

inline auto o_negate = [](const int a) -> int {
    return -a;
};

inline auto o_sqroot = [](const int a) -> double {
    return sqrt(a);
};

// Function token functions

inline auto f_add = [](const int a, const int b) -> int {
    return a + b;
};

inline auto f_sub = [](const int a, const int b) -> int {
    return a - b;
};

inline auto f_subtract = [](const int a, const int b) -> int {
    return a - b;
};

inline auto f_multiply = [](const int a, const int b) -> int {
    return a * b;
};

inline auto f_divide = [](const int a, const int b) -> int {
    return a / b;
};

inline auto f_max = [](const int a, const int b) -> int {
    return std::max(a, b);
};

inline auto f_min = [](const int a, const int b) -> int {
    return std::min(a, b);
};

#endif //FUNCS_H
