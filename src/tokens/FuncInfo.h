//
// Created by Andrii Klykavka on 09.07.2025.
//

#ifndef FUNCINFO_H
#define FUNCINFO_H

#include "Token.h"

struct FuncInfo {
    std::vector<std::string> args;
    std::vector<Token> tokenized_body;
};

#endif //FUNCINFO_H
