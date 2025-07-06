#include <iostream>

#include "Interpreter.h"

int main()
{
    Interpreter interpreter = Interpreter();

    std::string input;
    while (true) {
        std::cout << ">> ";
        std::getline(std::cin, input);
        if (input == "/exit") break;
        interpreter.interprete_line(input);
    }
    return 0;
}
